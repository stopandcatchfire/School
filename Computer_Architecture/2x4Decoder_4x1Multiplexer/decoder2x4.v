///////////////////////////////////////////////////////////////////
//Decoder2x4 for CSC137
//Written By Nick Wantz
//V1 9/6/16
//
//
///////////////////////////////////////////////////////////////////


module DecoderMod(s1, s0, o0, o1, o2, o3);	//module definition

	input s1, s0;
	output o0, o1, o2, o3;

	wire s1_inv, s0_inv, o0, o1, o2, o3;

//following provides logic gates
	not(s1_inv, s1);
	not(s0_inv, s0);
	and(o0, s1_inv, s0_inv);
	and(o1, s1_inv, s0);
	and(o2, s1, s0_inv);
	and(o3, s1, s0);
endmodule



module TestMod;
	reg s1, s0;		//2 1-bit flip flops
	wire o0, o1, o2, o3;	//4 outgoing wires

	DecoderMod my_decoder(s1, s0, o0, o1, o2, o3);	//creates instance

	initial begin
		$monitor("%0d\t%b\t%b\t%b\t%b\t%b\t%b", $time, s1, s0, o0, o1, o2, o3);
		$display("Time\ts1\ts0\to0\to1\to2\to3");
		$display("----------------------------------------------------");
	end

	initial begin
		s1=0;
		s0=0;
		#1;
		s1=0;
		s0=1;
		#1;
		s1=1;
		s0=0;
		#1;
		s1=1;
		s0=1;
		#1;
	end
endmodule

