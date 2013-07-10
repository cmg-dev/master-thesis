onbreak resume
onerror resume
vsim -novopt work.filter_tb
add wave sim:/filter_tb/u_filter2/clk
add wave sim:/filter_tb/u_filter2/clk_enable
add wave sim:/filter_tb/u_filter2/reset
add wave sim:/filter_tb/u_filter2/filter_in
add wave sim:/filter_tb/u_filter2/filter_out
add wave sim:/filter_tb/filter_out_ref
run -all
