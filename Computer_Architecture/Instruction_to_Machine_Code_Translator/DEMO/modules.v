// modules.v
//
// MEMmod
// PCmod
// Imod
// ARorIRmod
// BusMod

module MEMmod(Read, addr, output_buffer);
   ...
   initial $readmemb("indirect_inst.txt", MEM);
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

module ARorIRmod (what_on_bus, ld, storage);  // for both AR and IR
   ...
endmodule

module BusMod(addr, IRout, data, x2, x5, x7, BusOut);
   ...
endmodule

