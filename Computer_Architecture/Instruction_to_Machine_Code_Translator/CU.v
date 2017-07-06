//CU.v

module CUmod (clk, op, Iout, inrPC, Read, ldAR, ldIR, ldI, x2, x5, x7, T);
   input [2:0] op;
   input clk,Iout;
   output inrPC,Read,ldAR,ldIR,ldI,x2,x5,x7;
   output [0:15] T;
   
   wire clrSC;
   wire inrPC,Read,ldAR,ldIR,ldI,x2,x5,x7; // internal signal
   wire [0:7] D;
   wire [0:15] T;

   SequencerMod my_seq(clk,T,clrSC);
   DecoderMod my_dec(op,D);
   SignalDefinerMod my_sig(T,D,Iout,inrPC,Read,ldAR,ldIR,ldI,x2,x5,x7,clrSC);

endmodule

//carry out signal definitions (paper HW #1)
module SignalDefinerMod(T, D, Iout, inrPC, Read, ldAR, ldIR, ldI, x2, x5, x7, clrSC);
   input [0:15] T;
   input [0:7] D;
   input Iout;
   output x2,x5,x7,Read,clrSC,inrPC,ldAR,ldIR,ldI;

   wire and_ldAR,and_x7,and_Read;


   or(x2,T[0]);
   or(ldAR,T[1],and_ldAR,T[6]);
   or(Read,T[2],and_Read);
   or(x7,T[3],and_x7);
   or(inrPC,T[4]);
   or(ldIR,T[4]);
   or(x5,T[5]);
   or(ldI,T[6]);
   or(clrSC,T[10]);
   not(d7_inv,D[7]);
   and(and_ldAR,d7_inv,Iout,T[9]);
   and(and_x7,d7_inv,Iout,T[8]);
   and(and_Read,d7_inv,Iout,T[7]);

endmodule


module SequencerMod(clk,T,clrSC);
   input clk,clrSC;
   output [0:15] T;

   reg [0:15] T;

   initial T = 16'b0000_0000_0000_0001;
   always @(posedge clrSC) T = 16'b0000_0000_0000_0001;

   always @(posedge clk) begin
	T[0] <= T[15];
	T[1] <= T[0];
	T[2] <= T[1];
	T[3] <= T[2];
	T[4] <= T[3];
	T[5] <= T[4];
	T[6] <= T[5];
	T[7] <= T[6];
	T[8] <= T[7];
	T[9] <= T[8];
	T[10] <= T[9];
	T[11] <= T[10];
	T[12] <= T[11];
	T[13] <= T[12];
	T[14] <= T[13];
	T[15] <= T[14];
   end
endmodule

module DecoderMod(B,D);
   input [2:0] B;
   output [0:7] D;

   wire b0_inv,b1_inv,b2_inv;
   wire [0:7] D;

   not(b0_inv,B[0]);
   not(b1_inv,B[1]);
   not(b2_inv,B[2]);
   and(D[0],b0_inv,b1_inv,b2_inv);
   and(D[1],b2_inv,b1_inv,B[0]);
   and(D[2],b0_inv,B[1],b2_inv);
   and(D[3],b2_inv,B[1],B[0]);
   and(D[4],B[2],b1_inv,b2_inv);
   and(D[5],B[2],b1_inv,B[0]);
   and(D[6],B[2],B[1],b0_inv);
   and(D[7],B[2],B[1],B[0]);

endmodule
