module shuru_module
(
     input clk,
	  input rst,
     output sw1,
	  output sw2

);

reg [32:0]count;
parameter _2s=27'd80_000_000;
parameter _1s=26'd40_000_000;
	
/*********************************/
reg sw1r;
reg sw2r;
reg [3:0]i;
always @(posedge clk or negedge rst)
    if(!rst)
	  begin
	      sw1r<=1'b0;
		   count<=33'd0;
			sw2r<=1'b0;
	  end 
	 else 
		 begin
		    case(i)
			 0:
			 if(count==_1s)begin sw1r<=1'b1; i<=i<+1'b1; end
			 else count<=count+1'b1;
		
          1:begin sw1r<=1'b0; i<=i+1'b1;end 
			 
			 2:
			 if(count==_2s)begin sw2r<=1'b1; count<=33'd0; i<=i<+1'b1;end
			 else count<=count+1'b1;
			 
			 3:begin sw2r<=1'b0; i<=4'd0;end 
			 
          endcase
			 
		 end


/*********************************/
endmodule 