

#include <algorithm>
#include <cctype>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <utility>

class parser
{
public:
    void push(char c)
    {
        if(c=='\n')
            error("Invalid character");
        process_char(c);
    }

    std::vector<std::size_t> finalize() &&
    {
        process_char('\n');
        if(op_stack.size()!=1)
            error("Unmatched '('");
        return std::move(extra_paranthesis);
    }
private:
    constexpr static int max_prio = 100;

    std::vector<char> op_stack;

    std::vector<size_t> extra_paranthesis;

    std::vector<size_t> maybe_extra_paranthesis;
    
    std::size_t pos = 0;
    
    int required_min_prio = max_prio;
    
    bool post_paranthesis_decision = false;
    
    bool had_operand = false;

    [[noreturn]] void error(std::string s)
    {
        s += " at position ";
        s += std::to_string(pos);
        throw std::runtime_error(s);
    }

    static const int* priority(char op)
    {
        static const char ops[]       = {'(',')','\n','|','^','&','+','-','*','/'};
        static const int priorities[] = {-1 ,-1 ,0   , 1 , 2 , 3 , 4 , 4 , 5 , 5 };
        auto end = ops+sizeof ops;
        auto it = std::find(ops,end,op);
        return it!=end?priorities+(it-ops):nullptr;
    }

    void process_char(char c)
    {
        if(c=='('){
            if(had_operand)
                error("Opening parenthesis after operand");
            op_stack.push_back('(');
            maybe_extra_paranthesis.push_back(pos);
        }else{
            auto prio = priority(c);
            if(prio){
                if(!had_operand)
                    error("No operand before operation");
                had_operand = c==')';
                if(post_paranthesis_decision){
                    post_paranthesis_decision = false;
                    if(*prio>required_min_prio){
                        maybe_extra_paranthesis.pop_back();
                        maybe_extra_paranthesis.pop_back();
                    }else{
                        auto e = maybe_extra_paranthesis.end(),b = e-2;
                        extra_paranthesis.insert(extra_paranthesis.end(),b,e);
                        maybe_extra_paranthesis.erase(b,e);
                    }
                    required_min_prio = max_prio;
                }
                char last_removed = '\0';
                int cur_prio,min_popped_prio = max_prio;
                while(!op_stack.empty()&&(cur_prio=*priority(op_stack.back()))>=*prio){
                    last_removed = op_stack.back();
                    op_stack.pop_back();
                    if(last_removed=='(')
                        break;
                    min_popped_prio = std::min(min_popped_prio,cur_prio);
                }
                if(c==')'){
                    if(last_removed!='(')
                        error("Unmatched ')'");

                    if(maybe_extra_paranthesis.back()==std::string::npos)
                        maybe_extra_paranthesis.pop_back();
                    else{
                        required_min_prio = min_popped_prio;
                        maybe_extra_paranthesis.push_back(pos);
                        post_paranthesis_decision = true;
                    }
                }else{

                    if(op_stack.size()>1&&op_stack.back()=='('&&
                       *priority(op_stack.end()[-2])>=*prio)
                        maybe_extra_paranthesis.back() = std::string::npos;

                    op_stack.push_back(c);
                }
            }else if(islower(c)){
                if(had_operand)
                    error("Operand after operand");

                had_operand = true;
            }else
                error("Invalid character");
        }
        ++pos;
    }
};

int main()
{
    try{
        std::string expr;
        if(!getline(std::cin,expr))
            throw std::runtime_error("Input failed");
        parser p;
        for(char c:expr)
            p.push(c);
        auto skip_pos = std::move(p).finalize();
        std::sort(skip_pos.begin(),skip_pos.end());
        skip_pos.push_back(expr.size());
        std::size_t i = 0;
        for(auto sp:skip_pos){
            while(i<sp)
                std::cout << expr[i++];
            ++i;
        }
        std::cout << '\n';
    }
    catch(std::exception& e){
        std::cerr << e.what() << ".\n";
        return 1;
    }
}
