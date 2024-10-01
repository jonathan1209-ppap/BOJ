<?php
fscanf(STDIN, "%d\n", $T);
$dp = array_fill(0, 50+1, PHP_INT_MAX);
$dp[1] = 1;
$dp[2] = 2;
$dp[3] = 4;

for ($i=4;$i<22;$i++){
    $dp[$i]=$dp[$i-1]+$dp[$i-2]+$dp[$i-3];
}

for ($i=0;$i<$T;$i++){
    fscanf(STDIN, "%d\n", $a);
    fprintf(STDOUT,"%d\n",$dp[$a]);
}
?>
