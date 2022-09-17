package DataStructure.lab.experiment03;

public class Expression {
    /*返回将infix中缀表达式转化成的后缀表达式*/
    public static StringBuffer toPostfix(String infix){
        Stack<String> stack = new SeqStack<String>(infix.length());//运算符栈，顺序栈
        StringBuffer postfix = new StringBuffer(infix.length()*2);//后缀表达式字符串
        int i = 0;
        while (i < infix.length()){
            char ch = infix.charAt(i);
            switch (ch){
                /*
                若ch是运算符,将ch入栈,入栈之前，需要将ch与栈顶运算符进行比较
                若栈顶运算符优先级较高，则出栈，添加到postfix
                 */
                case '+':
                case '-':
                    while (!stack.isEmpty() && !stack.peek().equals("("))
                        postfix.append(stack.pop());
                    stack.push(ch + "");
                    i++;
                    break;
                case '*':
                case '/':
                    while (!stack.isEmpty() && (stack.peek().equals("*") || stack.peek().equals("/")))
                        postfix.append(stack.pop());        //栈顶优先级高的运算符出栈
                    stack.push(ch +"");
                    i++;
                    break;
                //若ch是'(',则入栈
                case '(':
                    stack.push(ch +"");
                    i++;
                    break;
                /*
                若ch是')',则若干运算符出栈，直到出栈的是左括号'(',表示一对括号匹配
                 */
                case ')':
                    String out = stack.pop();
                    while (out != null && ! out.equals("(")){  //直到出栈运算符为左括号'('
                        postfix.append(out);
                        out = stack.pop();
                    }
                    i++;
                    break;
                /*
                若ch是数字或者字母，则将其后的序列添加到postfix中,并添加空格最为分隔符
                 */
                default:
                    while (i < infix.length() && ch >= 'A' && ch <= 'z' || ch >='0' && ch <='9'){
                        postfix.append(ch);
                        i++;
                        if (i < infix.length())
                            ch = infix.charAt(i);
                    }
                    postfix.append(" ");
            }
        }
        //表达式结束时，将栈中运算符全部出栈，添加到postfix中
        while (!stack.isEmpty())
            postfix.append(stack.pop());
        return postfix;
    }
    //测试
    public static void main(String[] args) {
        //String infix = "123+10*(45-50+20)/((35-25)*2+10)-11";
        String infix = "A+B*(C-D*(E+F)/G+H)-(I+J)*K";
        System.out.println("infix:"+infix);
        StringBuffer postfix = toPostfix(infix);
        System.out.println("postfix:"+postfix);
    }
}
