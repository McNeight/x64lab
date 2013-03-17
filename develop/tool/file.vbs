
function file_rtext (sPath)
	dim fso,file
  sText = ""
	set fso = CreateObject("Scripting.FileSystemObject")            
  If fso.Fileexists(sPath) then 
		set file = fso.OpenTextFile(sPath,cREAD,false) 	
		sText = file.ReadAll
		file.Close
		set file = nothing
	end if
	set fso = nothing
	file_rtext = sText
end function

