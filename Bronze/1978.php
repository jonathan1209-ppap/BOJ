<?php
function isPrime($num) {
    if ($num <= 1) return false; 
    if ($num <= 3) return true;  
    if ($num % 2 == 0 || $num % 3 == 0) return false; 
    
    $i = 5;
    while ($i * $i <= $num) {
        if ($num % $i == 0 || $num % ($i + 2) == 0) return false;
        $i += 6;
    }
    
    return true;
}

fscanf(STDIN,"%d",$a);
$array = array_map('intval',explode(' ',trim(fgets(STDIN))));

$res = 0;
foreach ($array as $num){
	if (isPrime($num)){
		$res++;	
	}
}

fprintf(STDOUT,"%d",$res);
?>
