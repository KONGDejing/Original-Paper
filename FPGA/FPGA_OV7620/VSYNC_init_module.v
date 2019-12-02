module VSYNC_init_module
(
       CLK,RSTn,
       Pin_VSYNC,
       L2H_Sig_V,
		 H2L_Sig_V,
		

);
input CLK;
input RSTn;
input Pin_VSYNC;
output L2H_Sig_V;
output H2L_Sig_V;


/******************************/
reg L2H_F1;
reg L2H_F2;
reg H2L_F1;
reg H2L_F2;
always @ (posedge CLK or negedge RSTn)
   if(!RSTn)
		begin
			  L2H_F1<=1'd0;
			  L2H_F2<=1'd0;
			  H2L_F1<=1'd1;
			  H2L_F2<=1'd1;
		end
	else
	   begin
		     L2H_F1<=Pin_VSYNC;
			  L2H_F2<=L2H_F1;
			  H2L_F1<=Pin_VSYNC;
			  H2L_F2<=H2L_F1;
		end
	


/*******************************/
	
assign 	L2H_Sig_V=L2H_F1&!L2H_F2;
assign   H2L_Sig_V=!H2L_F1&H2L_F2;	

	
	
endmodule
	