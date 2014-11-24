$fn=60;

total_height = 2.75;
end_height = 1.0;
total_length = 60;
total_width = 10;

rotate([180,0,0]) difference() {
	union() {
		cylinder(d=13,h=total_height);
		translate([-3,-5,0]) cube([total_length + 3,10,total_height]);
		translate([total_length,0,0]) cylinder(d=10,h=total_height);
	}
	
	union() {
		linear_extrude(2) {
			circle(r=4);
			translate([16.25,0]) circle(r=2);
			polygon([[0,-4],[0,4],[16.25,2],[16.25,-2]]);
		}
	}
	
	cylinder(d=2.75,h=total_height);

	for (distance = [4.5:2:16.5]) {
		translate([distance,0,0]) cylinder(d=1.6,h=total_height+1);
	}
	
	translate([25,-total_width/2-.1,0]) difference() {
		cube([total_length-12,total_width+.2,total_height-end_height]);
		translate([0,total_width/2,0]) resize([total_width*2,total_width,0],auto=true) cylinder(d=total_width, h=total_height-end_height);
	}
	
	/* translate([22,-total_width/2-.1,total_height-.2]) rotate([-90,0,0]) linear_extrude(total_width+.2) {
		polygon([[0,total_height],[total_length - 17,total_height],[total_length-17,end_height],[10,end_height]]);
	} */
}
