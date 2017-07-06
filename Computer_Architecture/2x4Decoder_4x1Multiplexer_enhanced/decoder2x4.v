///////////////////////////////////////////////////////////////////
//Decoder2x4 for CSC137
//Written By Nick Wantz
//V1 9/6/16
//
//
///////////////////////////////////////////////////////////////////


module DecoderMod(s, o);	//module definition

	input [1:0] s;
	output [3:0] o;

	wire [1:0] s_inv;

//following provides logic gates
	not(s_inv[1], s[1]);
	not(s_inv[0], s[0]);
	and(o[0], s_inv[1], s_inv[0]);
	and(o[1], s_inv[1], s[0]);
	and(o[2], s[1], s_inv[0]);
	and(o[3], s[1], s[0]);
endmodule



module TestMod;
	reg [1:0] s;		//2 1-bit flip flops
	wire [3:0] o;	//4 outgoing wires

	DecoderMod my_decoder(s, o);	//creates instance

	initial begin
		$monitor("%0d\t%b\t%b\t%b\t%b\t%b\t%b", $time, s[1], s[0], o[0], o[1], o[2], o[3]);
		$display("Time\ts1\ts0\to0\to1\to2\to3");
		$display("----------------------------------------------------");
	end

	initial begin
		s[1]=0;
		s[0]=0;
		#1;
		s[1]=0;
		s[0]=1;
		#1;
		s[1]=1;
		s[0]=0;
		#1;
		s[1]=1;
		s[0]=1;
		#1;
	end
endmodule

