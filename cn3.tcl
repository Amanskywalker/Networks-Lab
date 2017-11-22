# This script is created by NSG2 beta1
# <http://wushoupong.googlepages.com/nsg>

#===================================
#     Simulation parameters setup
#===================================
set val(stop)   10.0                         ;# time of simulation end

#===================================
#        Initialization        
#===================================
#Create a ns simulator
set ns [new Simulator]

#Open the NS trace file
set tracefile [open cn3.tr w]
$ns trace-all $tracefile

#Open the NAM trace file
set namfile [open cn3.nam w]
$ns namtrace-all $namfile

#===================================
#        Nodes Definition        
#===================================
#Create 6 nodes
set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]
set n4 [$ns node]
set n5 [$ns node]

#===================================
#        Links Definition        
#===================================
#Createlinks between nodes
$ns duplex-link $n0 $n2 1.0Mb 10ms DropTail
$ns queue-limit $n0 $n2 5
$ns duplex-link $n1 $n2 10.0Mb 10ms DropTail
$ns queue-limit $n1 $n2 3
$ns duplex-link $n2 $n3 10.0Kb 10ms DropTail
$ns queue-limit $n2 $n3 5
$ns duplex-link $n3 $n4 100.0Kb 10ms DropTail
$ns queue-limit $n3 $n4 1
$ns duplex-link $n3 $n5 10.0Mb 10ms DropTail
$ns queue-limit $n3 $n5 6

#Give node position (for NAM)
$ns duplex-link-op $n0 $n2 orient right-down
$ns duplex-link-op $n1 $n2 orient right-up
$ns duplex-link-op $n2 $n3 orient right
$ns duplex-link-op $n3 $n4 orient right-up
$ns duplex-link-op $n3 $n5 orient right-down

#===================================
#        Agents Definition        
#===================================
	set ping0 [new Agent/Ping] 	
	$ns attach-agent $n0 $ping0
	set ping1 [new Agent/Ping]
	$ns attach-agent $n1 $ping1
	set ping4 [new Agent/Ping]
	$ns attach-agent $n4 $ping4
	set ping5 [new Agent/Ping]
	$ns attach-agent $n5 $ping5
	$ns connect $ping0 $ping4 
	$ns connect $ping1 $ping5 
	proc sendPingPacket {} {
		global ns ping0 ping1
		set time 0.01
		set now [$ns now]
		$ns at [expr $now + $time] "$ping0 send"
		$ns at [expr $now + $time] "$ping1 send"
		$ns at [expr $now + $time] "sendPingPacket"
	}
   	Agent/Ping instproc recv {from rtt} {
		global seq
		$self instvar node_
	}
	$ns at 0.01 "sendPingPacket"
	$ns at 10.0 "finish"
#===================================
#        Applications Definition        
#===================================

#===================================
#        Termination        
#===================================
#Define a 'finish' procedure
proc finish {} {
    global ns tracefile namfile
    $ns flush-trace
    close $tracefile
    close $namfile
    exec nam out.nam &
    exit 0
}
$ns at $val(stop) "$ns nam-end-wired $val(stop)"
$ns at $val(stop) "finish"
$ns at $val(stop) "puts \"done\" ; $ns halt"
$ns run
