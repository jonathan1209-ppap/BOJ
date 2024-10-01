<?php
function sieve($max) {
    $prime = array_fill(0, $max + 1, true);
    $prime[0] = $prime[1] = false;

    for ($i = 2; $i * $i <= $max; $i++) {
        if ($prime[$i]) {
            for ($j = $i * $i; $j <= $max; $j += $i) {
                $prime[$j] = false;
            }
        }
    }

    return $prime;
}

function printPrimes($m, $n) {
    $prime = sieve($n);
    for ($i = $m; $i <= $n; $i++) {
        if ($prime[$i]) {
            echo $i . PHP_EOL;
        }
    }
}

$input = trim(fgets(STDIN));
list($m, $n) = explode(' ', $input);
$m = (int)$m;
$n = (int)$n;

printPrimes($m, $n);
?>
