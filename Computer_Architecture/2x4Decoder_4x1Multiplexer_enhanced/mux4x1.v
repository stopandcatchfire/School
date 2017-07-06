/////////////////////////////////////////////////////
//Multiplexer4x1 for CSC137
//Written by Nick Wantz
//V1 9/6/16
//
//
/////////////////////////////////////////////////////


module DecoderMod(s, o);
	input [1:0]s;
	output [3:0] o;
	
	not(o[0], s[0]);
	not(o[2], s[1]);

	assign o[1] = s[0]; 
	assign o[3] = s[1];
endmodule


module MuxMod(s, d, o);
	input [1:0] s;
	input [3:0] d;
	output o;

	wire [3:0] s_decoded;
	wire [3:0] and_out;

	DecoderMod my_decoder(s, s_decoded);

	and(and_out[0], s_decoded[2], s_decoded[0], d[0]);
	and(and_out[1], s_decoded[2], s[0], d[1]);
	and(and_out[2], s[1], s_decoded[0], d[2]);
	and(and_out[3], s[1], s[0], d[3]);
	or(o, and_out[0], and_out[1], and_out[2], and_out[3]);
endmodule

module TestMod;
	reg [1:0] s;
	reg [3:0] d;
	wire o;

	MuxMod my_mux(s, d, o);

//not sure how many cycles to run, maybe 64 according to readme.txt


	initial begin 
		$display("Time\ts1\ts0\td0\td1\td2\td3\to");
		$display("----------------------------------------------------------");
		$monitor("%0d\t%b\t%b\t%b\t%b\t%b\t%b\t%b", $time, s[1], s[0], d[0], d[1], d[2] ,d[3], o);
	end

	initial begin
		#63;
		$finish;
	end


	always begin
		d[3]=0;
		#1;
		d[3]=1;
		#1;
	end
	
	always begin
		d[2]=0;
		#2;
		d[2]=1;
		#2;
	end
	
	always begin
		d[1]=0;
		#4;
		d[1]=1;
		#4;
	end

	always begin
		d[0]=0;
		#8;
		d[0]=1;
		#8;
	end

	always begin
		s[0]=0;
		#16;
		s[0]=1;
		#16;
	end

	always begin
		s[1]=0;
		#32;
		s[1]=1;
		#32;
	end

endmodule
