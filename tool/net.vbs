
'--- credits to
'--- http://vbscriptautomation.net/73/download-files-using-vbscript/
'--- download file from url to local
'--- RETURN 0=err 1=OK

function net_dload(sFileURL, sLocation)
	'create xmlhttp object
	retVal = 0
	Set objXMLHTTP = CreateObject("MSXML2.XMLHTTP")
	'get the remote file
	objXMLHTTP.open "GET", sFileURL, false
	'send the request
	objXMLHTTP.send()
	'wait until the data has downloaded successfully
	do until ((objXMLHTTP.Status = 200) or (objXMLHTTP.Status = 404))
		wscript.sleep(1000) 
	loop
	'if the data has downloaded sucessfully
  
	If objXMLHTTP.Status = 200 Then
    '--- create binary stream object
		Set objADOStream = CreateObject("ADODB.Stream")
		objADOStream.Open
    '--- adTypeBinary
		objADOStream.Type = 1
		objADOStream.Write objXMLHTTP.ResponseBody
    '--- Set the stream position to the start
		objADOStream.Position = 0    
   '--- create file system object to allow the script to check for an existing file
    Set objFSO = Createobject("Scripting.FileSystemObject")
     'check if the file exists, if it exists then delete it
		If objFSO.Fileexists(sLocation) then _
			objFSO.DeleteFile sLocation
    'destroy file system object
		set objFSO = Nothing
    'save the ado stream to a file
		objADOStream.SaveToFile sLocation
    'close the ado stream
		objADOStream.Close
		'destroy the ado stream object
		set objADOStream = Nothing
	'end object downloaded successfully
    retVal = 1
	end if
	'destroy xml http object
	Set objXMLHTTP = Nothing
  net_dload = retVal
end function

'--- get url text
'--- RET 0=err/text=OK
function net_get_page(sFileURL)
	'create xmlhttp object
	sText = ""
	Set objXMLHTTP = CreateObject("MSXML2.XMLHTTP")
	'get the remote file
	objXMLHTTP.open "GET", sFileURL, false
	'send the request
	objXMLHTTP.send()
	'wait until the data has downloaded successfully
	do until ((objXMLHTTP.Status = 200) or (objXMLHTTP.Status = 404))
		wscript.sleep(1000) 
	loop
	'if the data has downloaded sucessfully
  
	If objXMLHTTP.Status = 200 Then
		sText = objXMLHTTP.ResponseText
	end if
	'destroy xml http object
	Set objXMLHTTP = Nothing
  net_get_page = sText
end function


