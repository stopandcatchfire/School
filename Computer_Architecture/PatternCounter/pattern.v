//Nick Wantz
//CSc 137
//HW6

module TestMod;
   reg CLK;
   wire [0:8] Q;
   wire [0:6] C;

   always begin // this is clock wave
      CLK = 0;  // 0 for half cycle (#1)
      #1;
      CLK = 1;  // 1 for half cycle (#1)
      #1;
   end

   RippleMod my_ripple(CLK,Q);
   CoderMod my_coder(Q,C);

   initial #36 $finish;

   initial begin
      $display("Q         | C        |");
      $monitor("%b%b%b%b%b%b%b%b%b | %b%b%b %b%b%b%b | %c ", Q[0], Q[1], Q[2], Q[3], Q[4], Q[5], Q[6], Q[7], Q[8], C[0], C[1], C[2], C[3], C[4], C[5], C[6], C);
   end
endmodule

module CoderMod(Q,C);
   input [0:8] Q;
   output [0:6] C;

   or(C[0], Q[0], Q[1], Q[2], Q[3], Q[4], Q[5], Q[6], Q[7], Q[8]);
   or(C[1], Q[1], Q[2], Q[3], Q[5], Q[6], Q[7], Q[8]);
   or(C[2], Q[4], Q[7], Q[8]);
   or(C[3], Q[0], Q[1], Q[3], Q[6], Q[8]);
   or(C[4], Q[0], Q[4], Q[6], Q[7]); 
   or(C[5], Q[0], Q[2], Q[3], Q[4], Q[6], Q[8]);
   or(C[6], Q[1], Q[2], Q[3], Q[4], Q[5]);
	
endmodule

module RippleMod(CLK,Q);
   input CLK;
   output [0:8] Q;

   reg [0:8] Q;

   always @(posedge CLK) begin
	Q[0] <= Q[8];
	Q[1] <= Q[0];
	Q[2] <= Q[1];
	Q[3] <= Q[2];
	Q[4] <= Q[3];
	Q[5] <= Q[4];
	Q[6] <= Q[5];
	Q[7] <= Q[6];
	Q[8] <= Q[7];
   end

   initial begin // here we conveniently set flipflops to 1000 (binary)
 	Q[0] = 1;
	Q[1] = 0;
	Q[2] = 0;
	Q[3] = 0;
	Q[4] = 0;
	Q[5] = 0;   
	Q[6] = 0;
	Q[7] = 0;
	Q[8] = 0;
	end
endmodule

