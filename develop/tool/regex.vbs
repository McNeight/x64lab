
function regex_all (sText,sNeedle,arrMatches)
 dim re, Match, Matches

 ' Create the regular expression.
 set re = new RegExp
 re.Pattern = sNeedle
 re.IgnoreCase = false
 re.Global = true
 're.Multiline = true
 
 ' Perform the search.
 set Matches = re.Execute(sText)
 ' Iterate through the Matches collection.
 index = 0
 if Matches.Count > 0 then
	redim arrMatches (Matches.Count-1,1)
	for each Match in Matches
		'--- 	' Show the submatches.
	'--- 		s = index & " - " & Match.Submatches(0)
	'--- 		s = s & " - " & Match.Submatches(1)
	'--- 		wscript.echo s
		arrMatches(index,0)=Match.Submatches(0)	'--- filename
		arrMatches(index,1)=Match.Submatches(1) '--- description
		index = index + 1
	next
 end if
 '---  'wscript.echo (Match.FirstIndex & " - " & Match.Value)
 '--- 	'wscript.echo (Match.Length & " - " & Match.Value)
 regex_all = Matches.Count
end function


