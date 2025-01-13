#ifndef PRESETS_H
#define PRESETS_H

class Presets {
	
	private:

		float density;
		float friction;
		float restitution;

	public:

		Presets (float density, float friction, float restitution);

		float getDensity ();
		float getFriction ();
		float getRestitution ();

};

#endif