/////////////////////////////////////////////////////
//Multiplexer4x1 for CSC137
//Written by Nick Wantz
//V1 9/6/16
//
//
/////////////////////////////////////////////////////


module MuxMod(s1, s0, d0, d1, d2, d3, o);
	input s1, s0, d0, d1, d2, d3;
	output o;

	wire s1_inv, s0_inv, and0, and1, and2, and3;

	not(s1_inv, s1);
	not(s0_inv, s0);
	and(and0, s1_inv, s0_inv, d0);
	and(and1, s1_inv, s0, d1);
	and(and2, s1, s0_inv, d2);
	and(and3, s1, s0, d3);
	or(o, and0, and1, and2, and3);
endmodule

module TestMod;
	reg s1, s0, d0, d1, d2, d3;
	wire o;

	MuxMod my_mux(s1, s0, d0, d1, d2, d3, o);

//not sure how many cycles to run, maybe 64 according to readme.txt


	initial begin 
		$display("Time\ts1\ts0\td0\td1\td2\td3\to");
		$display("----------------------------------------------------------");
		$monitor("%0d\t%b\t%b\t%b\t%b\t%b\t%b\t%b", $time, s1, s0, d0, d1, d2 ,d3, o);
	end

	initial begin
		s1=0;s0=0;d0=0;d1=0;d2=0;d3=0;
		#1;
		s1=0;s0=0;d0=0;d1=0;d2=0;d3=1;
		#1;
		s1=0;s0=0;d0=0;d1=0;d2=1;d3=0;
		#1
		s1=0;s0=0;d0=0;d1=0;d2=1;d3=1;
		#1; 	
		s1=0;s0=0;d0=0;d1=1;d2=0;d3=0;
		#1; 	
		s1=0;s0=0;d0=0;d1=1;d2=0;d3=1;
		#1; 	
		s1=0;s0=0;d0=0;d1=1;d2=1;d3=0;
		#1; 	
		s1=0;s0=0;d0=0;d1=1;d2=1;d3=1;
		#1; 	
		s1=0;s0=0;d0=1;d1=0;d2=0;d3=0;
		#1; 	
		s1=0;s0=0;d0=1;d1=0;d2=0;d3=1;
		#1; 	
		s1=0;s0=0;d0=1;d1=0;d2=1;d3=0;
		#1; 	
		s1=0;s0=0;d0=1;d1=0;d2=1;d3=1;
		#1; 	
		s1=0;s0=0;d0=1;d1=1;d2=0;d3=0;
		#1; 	
		s1=0;s0=0;d0=1;d1=1;d2=0;d3=1;
		#1; 							
		s1=0;s0=0;d0=1;d1=1;d2=1;d3=0;
		#1; 
		s1=0;s0=0;d0=1;d1=1;d2=1;d3=1; 
		#1;
//first iteration end
		s1=0;s0=1;d0=0;d1=0;d2=0;d3=0;
		#1; 
		s1=0;s0=1;d0=0;d1=0;d2=0;d3=1;
		#1;
		s1=0;s0=1;d0=0;d1=0;d2=1;d3=0;
		#1
		s1=0;s0=1;d0=0;d1=0;d2=1;d3=1;
		#1; 	
		s1=0;s0=1;d0=0;d1=1;d2=0;d3=0;
		#1; 	
		s1=0;s0=1;d0=0;d1=1;d2=0;d3=1;
		#1; 	
		s1=0;s0=1;d0=0;d1=1;d2=1;d3=0;
		#1; 	
		s1=0;s0=1;d0=0;d1=1;d2=1;d3=1;
		#1; 	
		s1=0;s0=1;d0=1;d1=0;d2=0;d3=0;
		#1; 	
		s1=0;s0=1;d0=1;d1=0;d2=0;d3=1;
		#1; 	
		s1=0;s0=1;d0=1;d1=0;d2=1;d3=0;
		#1; 	
		s1=0;s0=1;d0=1;d1=0;d2=1;d3=1;
		#1; 	
		s1=0;s0=1;d0=1;d1=1;d2=0;d3=0;
		#1; 	
		s1=0;s0=1;d0=1;d1=1;d2=0;d3=1;
		#1; 							
		s1=0;s0=1;d0=1;d1=1;d2=1;d3=0;
		#1; 
		s1=0;s0=1;d0=1;d1=1;d2=1;d3=1; 
		#1; 
//second iteration end
		s1=1;s0=0;d0=0;d1=0;d2=0;d3=0;
		#1; 
		s1=1;s0=0;d0=0;d1=0;d2=0;d3=1;
		#1;
		s1=1;s0=0;d0=0;d1=0;d2=1;d3=0;
		#1
		s1=1;s0=0;d0=0;d1=0;d2=1;d3=1;
		#1; 	
		s1=1;s0=0;d0=0;d1=1;d2=0;d3=0;
		#1; 	
		s1=1;s0=0;d0=0;d1=1;d2=0;d3=1;
		#1; 	
		s1=1;s0=0;d0=0;d1=1;d2=1;d3=0;
		#1; 	
		s1=1;s0=0;d0=0;d1=1;d2=1;d3=1;
		#1; 	
		s1=1;s0=0;d0=1;d1=0;d2=0;d3=0;
		#1; 	
		s1=1;s0=0;d0=1;d1=0;d2=0;d3=1;
		#1; 	
		s1=1;s0=0;d0=1;d1=0;d2=1;d3=0;
		#1; 	
		s1=1;s0=0;d0=1;d1=0;d2=1;d3=1;
		#1; 	
		s1=1;s0=0;d0=1;d1=1;d2=0;d3=0;
		#1; 	
		s1=1;s0=0;d0=1;d1=1;d2=0;d3=1;
		#1; 							
		s1=1;s0=0;d0=1;d1=1;d2=1;d3=0;
		#1; 
		s1=1;s0=0;d0=1;d1=1;d2=1;d3=1; 
		#1; 
//third iteration end
		s1=1;s0=1;d0=0;d1=0;d2=0;d3=0;
		#1; 
		s1=1;s0=1;d0=0;d1=0;d2=0;d3=1;
		#1;
		s1=1;s0=1;d0=0;d1=0;d2=1;d3=0;
		#1
		s1=1;s0=1;d0=0;d1=0;d2=1;d3=1;
		#1;	
		s1=1;s0=1;d0=0;d1=1;d2=0;d3=0;
		#1; 	
		s1=1;s0=1;d0=0;d1=1;d2=0;d3=1;
		#1; 	
		s1=1;s0=1;d0=0;d1=1;d2=1;d3=0;
		#1; 	
		s1=1;s0=1;d0=0;d1=1;d2=1;d3=1;
		#1; 	
		s1=1;s0=1;d0=1;d1=0;d2=0;d3=0;
		#1; 	
		s1=1;s0=1;d0=1;d1=0;d2=0;d3=1;
		#1; 	
		s1=1;s0=1;d0=1;d1=0;d2=1;d3=0;
		#1; 	
		s1=1;s0=1;d0=1;d1=0;d2=1;d3=1;
		#1; 	
		s1=1;s0=1;d0=1;d1=1;d2=0;d3=0;
		#1; 	
		s1=1;s0=1;d0=1;d1=1;d2=0;d3=1;
		#1; 							
		s1=1;s0=1;d0=1;d1=1;d2=1;d3=0;
		#1; 
		s1=1;s0=1;d0=1;d1=1;d2=1;d3=1; 
		#1; 
//fourth iteration end
	end
endmodule
