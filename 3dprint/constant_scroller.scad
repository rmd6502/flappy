$fn=50;
difference() {
	union() {
		cylinder(h=5,d=19.15);
		translate([-17,-3.5,0]) cube([34,7,1]);
	}
	translate([0,0,3.25]) cylinder(d=6.25,h=3.25);
	translate([0,0,1]) rotate_extrude() polygon(points=[[0,0],[0,2.5],[3.75,2.5]]);
	cylinder(d=2.75,h=10);
	for (dist=[0:2:10]) {
		translate([5+dist,0,0]) cylinder(d=1.6,h=1);
		translate([-(5+dist),0,0]) cylinder(d=1.6,h=1);
	}
	difference() {
		cylinder(d=8.25,h=1);
		cylinder(d=3.4,h=1);
	}
}