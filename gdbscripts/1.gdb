define pstrtab
	set $i = 0
	while $arg0[$i] != (void*)0
		print $arg0[$i]
		set $i = $i + 1
	end
end

define plist
	set $i = $arg0
	while ($i) != (void*)0
		print (($i)->content)
		set $i = $i->next
	end
end
set follow-fork-mode parent
b main.c:91
run
set follow-fork-mode child
b ft_run_child_2
c
