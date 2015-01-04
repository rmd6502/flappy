$fn=20;
height=30;
width=20;
depth=6;

union() {
	difference() {
		cube ([width, depth, height]);
		translate([3.5,-.1,height-8]) cube([13, 6.2, 6]);
	}
	difference() {
		translate([-10,-2,-3]) cube([40,10,3]);
		translate([-5,3,-3]) cylinder(d=2.5,h=3);
		translate([25,3,-3]) cylinder(d=2.5,h=3);
	}
	translate([7.5,0,0]) support();
	translate([12.5,6,0]) rotate([0,0,180]) support();
	translate([3.5,0,height-2]) rotate([90,0,90]) resize([6,1.5,6.5]) support();
	translate([16.5,6,height-2]) rotate([90,0,-90]) resize([6,1.5,6.5]) support();
}

module support()
{
	polyhedron(points=[[0,0,0],[0,0,height*.7],[5,0,height*.7],[5,0,0],[0,-2,0],[5,-2,0]],faces=[[0,3,2,1],[1,2,5,4],[0,1,4],[2,3,5],[0,4,5,3]]);
}