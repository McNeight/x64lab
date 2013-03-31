public cin,cout,cargs

sub io_set()
	set cin = WScript.StdIn
	set cout = WScript.StdOut
	set cargs = Wscript.Arguments
end sub

sub io_unset()
	set cin = nothing
	set cout = nothing
	set cargs = nothing
end  sub

