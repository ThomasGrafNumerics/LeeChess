set term gif animate size 1024,768
set output "animation.gif"

do for [t=0:360] {
	set view 60, t
	splot "xorshift32data.dat" with dots
}
