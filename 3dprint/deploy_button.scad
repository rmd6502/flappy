$fn=80;

difference() {
	union() {
		resize([50,50,25]) sphere(50);
		intersection() {
			translate([-22,-3,0]) linear_extrude(15) text(text="Annihilate",size=7);
			resize([52.5,52.5,27.5]) sphere(52.5);
		}
	}
	translate([-25,-25,-12.5]) cube([50,50,12.5]);
	cylinder (h=4,d=6.5);
}

