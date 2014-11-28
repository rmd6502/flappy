include<MCAD/nuts_and_bolts.scad>;

$fn=60;

module opto(diameter, height,tint=[1,1,1],lead_spacing=2.54,collar_width=.9,collar_height=1)
{
	assign(radius=diameter/2) {
		 union() {
			color(tint,.8) {
				translate([0,0,height-radius]) difference() {
					sphere(radius);
					translate([-radius,-radius,-radius]) cube([radius*2,radius*2,radius]);
				}
				cylinder(r=radius, h=height-radius);
				difference() {
					cylinder(r=radius+collar_width/2,h=collar_height);
					translate([radius,-radius,-.01]) cube([collar_width,radius*2,collar_height+.02]);
				}
			}
			rotate([180,0,0]) translate([lead_spacing/2-.25,-.125,0]) color([0.7,0.7,0.7]) cube([.5,.25,10]);
			rotate([180,0,0]) translate([-lead_spacing/2-.25,-.125,0]) color([0.7,0.7,0.7]) cube([.5,.25,12]);
		}
	}
}

angle = 90-atan2(20,5);

module halfBlock()
{
	difference() {
		color([1.0,0.2,1.0]) translate([-7,0,-5]) cube([24,4,8]);
		rotate([0,angle,0])opto(diameter=3,height=5.25,collar_width=1,tint=[0.1,0.1,0.1]);
		rotate([0,angle,0])translate([-2,0,-6])cube([3.6,1,6]);
		translate([9+4*sin(angle),0,-3.35/2]) rotate([0,angle,180])opto(diameter=5,height=8.6,tint=[1,0,0]);
		translate([12.4+4*sin(angle),1,-3.35/2-5.3]) rotate([0,angle,180])cube([3.6,1.2,6]);
		translate([4.5,0,-5]) cylinder(d=3.3,h=6);
		translate([4.5,0,-5]) nutHole(3);
		translate([-4.3,5.5,-1]) rotate([90,0,0]) cylinder(d=3.3,h=6);
		translate([14.8,5.5,-1]) rotate([90,0,0]) cylinder(d=3.3,h=6);
	}
}

translate([12,0,0]) halfBlock();
translate([-12,0,0]) mirror([1,0,0]) halfBlock();