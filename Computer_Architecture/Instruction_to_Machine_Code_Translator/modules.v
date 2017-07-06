//modules.v
//


module MEMmod(Read, addr, output_buffer);
   input [11:0] addr;
   input Read;
   output [15:0] output_buffer;
	   
   reg [15:0] output_buffer;
   reg [15:0] MEM[15:0];

   always @(posedge Read) output_buffer = MEM[addr];
 
   initial $readmemb("instructions.txt", MEM);

endmodule

module PCmod(incr, Q);
   input incr;          // enable upcount
   output [15:0] Q;     // 16-bit output

   reg [15:0] Q;

   initial Q = 0;
   always @(posedge incr) Q = Q + 1; // simulated counting
endmodule

module Imod (what_on_bus, ldI, Iout);  // "I" is leftmost bit in IR
   input [15:0] what_on_bus;
   input ldI;
   output Iout;

   reg Iout;  // internal storage of this module "I"

   always @(posedge ldI) Iout = what_on_bus[15]; // once loaded, continuous output
endmodule

module ARorIRmod(what_on_bus, ld, storage);  // for both AR and IR
   input [15:0] what_on_bus;
   input ld;
   output [15:0] storage;

   reg [15:0] storage;

   always @(posedge ld) storage = what_on_bus;

   
endmodule

module BusMod(addr, IRout, data, x2, x5, x7, BusOut);
   input [15:0] addr,IRout,data;
   input x2,x5,x7;
   output [15:0] BusOut;

   reg [15:0] BusOut;
   wire x2,x5,x7;
   

   always @(posedge x2)
	if(x2)
	   begin
	      BusOut = addr;
	   end

   always @(posedge x5)
	if(x5)
	   begin
	      BusOut = IRout;
	   end

   always @(posedge x7)
	if(x7)
	   begin
	      BusOut = data;
	   end

endmodule

