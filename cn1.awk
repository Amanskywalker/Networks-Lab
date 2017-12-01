#!/usr/bin/awk -f

BEGIN{
	cbrpkt=0;
	tcppkt=0;
}
{
	if(($1=="d") && ($5=="cbr")){
	cbrpkt++
	}
	if(($1=="d") && ($5=="tcp")){
	tcppkt++
	}
}
END{
printf("\nNo of CBR packets dropped %d",cbrpkt);
printf("\nNo of TCP packets dropped %d\n",tcppkt);
}
