str="abcdefg" #0 1 2 3 4 ... len(str)

a : 0
b : 1

f : 5

#print(str[0:5]) #abcde
#print(str[0:5:2])  #ace

#print(str)                 # 输出字符串
#print(str[3])              # 输出字符串第一个字符
#print(str[2:5])            # 输出从第三个开始到第六个的字符（不包含）
#print(str[2:])             # 输出从第三个开始后的所有字符
#print(str[1:5:2])          # 输出从第二个开始到第五个且每隔一个的字符（步长为2）
#print(str[0:-1])           # 输出第一个到倒数第二个的所有字符
#print(str * 2)             # 输出字符串两次
#print(str + "123")         # 连接字符串
#print(str,123)

#print('------------------------------')
 
#print('hello world')      # 使用反斜杠(\)+n转义特殊字符
print(r'hello\nworld')     # 在字符串前面添加一个 r，表示原始字符串，不会发生转义
print("helloasdadad")