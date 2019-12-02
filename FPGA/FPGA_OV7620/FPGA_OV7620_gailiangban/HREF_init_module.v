 module HREF_init_module
(
       CLK,RSTn,
		 Pin_HREF,
       L2H_Sig_H	 

);
input CLK;
input RSTn;
input Pin_HREF;
output L2H_Sig_H;

/************************************/
reg L2H_F1;
reg L2H_F2;
always @ (posedge CLK or negedge RSTn)
    if(!RSTn)
	    begin
		      L2H_F1<=1'd0;
		      L2H_F2<=1'd0;
		 end
	 else
	    begin
		      L2H_F1<=Pin_HREF;
				L2H_F2<=L2H_F1;
		 end
/************************************/
assign L2H_Sig_H=L2H_F1&L2H_F2;




endmodule 