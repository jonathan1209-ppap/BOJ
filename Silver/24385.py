#  **************************************************************************  #
#                                                                              #
#                                                       :::    :::    :::      #
#    Problem Number: 24385                             :+:    :+:      :+:     #
#                                                     +:+    +:+        +:+    #
#    By: knen <boj.kr/u/knen>                        +#+    +#+          +#+   #
#                                                   +#+      +#+        +#+    #
#    https://boj.kr/24385                          #+#        #+#      #+#     #
#    Solved: 2024/09/03 20:36:08 by knen          ###          ###   ##.kr     #
#                                                                              #
#  **************************************************************************  #

from itertools import permutations

a=''.join(sorted(input()))
per=permutations(a)
s = sorted(set(''.join(x) for x in per))
print("\n".join(s))
