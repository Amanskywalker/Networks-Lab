set ns [new Simulator]
set f [open cn1.tr w]
set nf [open cn1.nam w]
$ns trace-all $f
$ns namtrace-all $nf

proc finish {} {
	global f nf ns
	$ns flush-trace
	close $f
	close $nf
exec nam out.nam &
exec ./cn1.awk cn1.tr &
	exit 0
}

set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]


$n0 label "TCP Source"
$n1 label "UDP Source"
$n2 label "Router"


$ns color 1 red
$ns color 2 blue


$ns duplex-link $n0 $n2 0.75Mb 10ms DropTail
$ns duplex-link $n1 $n2 0.75Mb 10ms DropTail


$ns queue-limit $n0 $n2 10
$ns queue-limit $n1 $n2 10

$ns duplex-link-op $n0 $n2 orient right-down
$ns duplex-link-op $n1 $n2 orient right-up


set udp0 [new Agent/UDP]
$ns attach-agent $n1 $udp0

set cbr0 [new Application/Traffic/CBR]
$cbr0 attach-agent $udp0
	
$cbr0 set packetSize_ 500
$cbr0 set interval_ 0.003

set null0 [new Agent/Null]
$ns attach-agent $n2 $null0

$ns connect $udp0 $null0

set tcp0 [new Agent/TCP]
$ns attach-agent $n0 $tcp0

set ftp0 [new Application/FTP]
$ftp0 attach-agent $tcp0
	
set sink [new Agent/TCPSink]
$ns attach-agent $n2 $sink

$ftp0 set maxPkts_ 500

$ns connect $tcp0 $sink

$ns at 0.1 "$cbr0 start"
$ns at 1.0 "$ftp0 start"
$ns at 4.0 "$ftp0 stop"
$ns at 4.5 "$cbr0 stop"
$udp0 set class_ 1
$tcp0 set class_ 2
$ns at 5.0 "finish"
$ns run

