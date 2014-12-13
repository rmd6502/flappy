$fn=50;
inch = 25.4;

height=15.5;

union() {

difference() {
	cube([1.5 * inch, 5, 2]);
	translate([.5*inch,2.5,0]) cylinder(d=3.25,h=2);
	translate([1*inch,2.5,0]) cylinder(d=3.25,h=2);
}

translate([.25*inch-2.5,1.5,2]) cube([5, 2, height-3]);
translate([1.25*inch-2.5,1.5,2]) cube([5,2,height-3]);

translate([.25*inch-2.5, 1.5, 9])rotate([90,0,90]) linear_extrude(5) polygon([[0,0],[2,0],[1.25,1.25],[.75,1.25]]);

translate([1.25*inch-2.5, 1.5, 9])rotate([90,0,90]) linear_extrude(5) polygon([[0,0],[2,0],[1.25,1.25],[.75,1.25]]);

translate([.25*inch+2.5, 0, height-1]) rotate([-90,0,90]) difference() {
	cylinder(r=3,h=5);
	cylinder(r=2.25,h=5);
	translate([-3,0,0]) cube([6,3,5]);
}

translate([1.25*inch+2.5, 0, height-1]) rotate([-90,0,90]) difference() {
	cylinder(r=3,h=5);
	cylinder(r=2.25,h=5);
	translate([-3,0,0]) cube([6,3,5]);
}

translate([.25*inch-2.5, -5.25, height-1]) rotate([90,0,90]) difference() {
	cylinder(r=3,h=5);
	cylinder(r=2.25,h=5);
	translate([-3,0,0]) cube([6,3,5]);
}

translate([1.25*inch-2.5, -5.25, height-1]) rotate([90,0,90]) difference() {
	cylinder(r=3,h=5);
	cylinder(r=2.25,h=5);
	translate([-3,0,0]) cube([6,3,5]);
}
}