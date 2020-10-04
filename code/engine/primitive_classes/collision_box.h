#ifndef COLLISION_BOX_H
#define COLLISION_BOX_H

class CollisionBox: public TriggerZone
{
	public:
		CollisionBox(int x, int y, int width, int height, bool activeStatus);
		void pushDrawableObjectOutsideCollisionBoxIfItIsIntersecting(DrawableObject& objectToPush) const;
	protected:
		//
	private:
		//
};

#endif
