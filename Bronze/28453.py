#  **************************************************************************  #
#                                                                              #
#                                                       :::    :::    :::      #
#    Problem Number: 28453                             :+:    :+:      :+:     #
#                                                     +:+    +:+        +:+    #
#    By: knen <boj.kr/u/knen>                        +#+    +#+          +#+   #
#                                                   +#+      +#+        +#+    #
#    https://boj.kr/28453                          #+#        #+#      #+#     #
#    Solved: 2024/09/04 19:16:30 by knen          ###          ###   ##.kr     #
#                                                                              #
#  **************************************************************************  #

a=int(input())
x=[*map(int,input().split())]

for l in x:
    if l>=300:print("1",end=" ")
    elif l>=275:print("2",end=" ")
    elif l>=250:print("3",end=" ")
    else:print("4",end=" ")
