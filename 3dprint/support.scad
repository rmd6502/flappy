$fn=30;
height=24;
width=30;
depth=6;
fillheight=10;

fill=width*13/20;

full_support = false;

difference() {
	union() {
		difference() {
			cube ([width, depth, height]);
			translate([(width-fill)/2,-.1,height-fillheight-2]) cube([fill, 6.2, fillheight]);
		}
		difference() {
			translate([-10,-2,-3]) cube([width+20,10,3]);
			translate([-5,3,-3]) cylinder(d=3.5,h=3);
			translate([width+5,3,-3]) cylinder(d=3.5,h=3);
		}
		if (full_support) {
			translate([(width+20)/2-12.5,0,0]) support();
			translate([(width+20)/2-7.5,6,0]) rotate([0,0,180]) support();
		} else {
			translate([(width-fill)/2-5,0,0]) support();
			translate([(width-fill)/2,6,0]) rotate([0,0,180]) support();
			translate([(width+fill)/2,0,0]) support();
			translate([(width+fill)/2+5,6,0]) rotate([0,0,180]) support();

		}
		translate([(width-fill)/2,0,height-2]) rotate([90,0,90]) resize([depth,1.5,fill/2]) support();
		translate([(width-fill)/2+fill,depth,height-2]) rotate([90,0,-90]) resize([depth,1.5,fill/2]) support();
	}
	if (!full_support) {
		translate([(width-fill)/2, -2, -3]) cube([fill, depth+4, height-fillheight+1]);
	}
}

module support()
{
	polyhedron(points=[[0,0,0],[0,0,height-fillheight-3],[5,0,height-fillheight-3],[5,0,0],[0,-2,0],[5,-2,0]],faces=[[0,3,2,1],[1,2,5,4],[0,1,4],[2,3,5],[0,4,5,3]]);
}