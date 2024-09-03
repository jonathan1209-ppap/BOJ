#  **************************************************************************  #
#                                                                              #
#                                                       :::    :::    :::      #
#    Problem Number: 16341                             :+:    :+:      :+:     #
#                                                     +:+    +:+        +:+    #
#    By: knen <boj.kr/u/knen>                        +#+    +#+          +#+   #
#                                                   +#+      +#+        +#+    #
#    https://boj.kr/16341                          #+#        #+#      #+#     #
#    Solved: 2024/09/03 20:59:04 by knen          ###          ###   ##.kr     #
#                                                                              #
#  **************************************************************************  #

import sys
input = sys.stdin.readline


a,b=map(int,input().split())
c,d=map(int,input().split())

if (abs(a-c)+abs(b-d))%2==0:
    print("black")
else:
    print("white")
