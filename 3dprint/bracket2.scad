$fn=20;
rotate([90,0,0])union() {
	cube ([2,5,14.5]);
	translate([-5,0,0]) difference() {
		cube([5,5,2]);
		translate([2.5,2.5,0]) cylinder(d=3,h=2);
	}
	translate([0,0,14.5]) cube([24,5,2]);
	translate([22,0,0]) cube([2,5,14.5]);
	translate([24,0,0]) difference() {
		cube([5,5,2]);
		translate([2.5,2.5,0]) cylinder(d=3,h=2);
	}
}