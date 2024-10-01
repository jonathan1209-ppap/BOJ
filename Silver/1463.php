<?php
fscanf(STDIN, "%d", $a);
$dp = array_fill(0, $a+1, PHP_INT_MAX);
$dp[1] = 0;

for ($i = 2; $i <= $a; $i++) {
    $dp[$i] = $dp[$i - 1] + 1;
    if ($i % 2 == 0) {
        $dp[$i] = min($dp[$i], $dp[$i / 2] + 1);
    }
    if ($i % 3 == 0) {
        $dp[$i] = min($dp[$i], $dp[$i / 3] + 1);
    }
}

echo $dp[$a];
?>
