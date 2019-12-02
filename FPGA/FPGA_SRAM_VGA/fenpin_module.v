module fenpin_module 
(
    input CLK,
	 input RSTn,
	 
	 output CLK1
);
reg CLKreg;
always @(posedge CLK or negedge RSTn)
    if(!RSTn)
	    CLKreg<=1'b0;
	 else
	    CLKreg=~CLKreg;
assign CLK1=CLKreg;	 
endmodule
