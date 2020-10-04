#include "collision_box.h"
CollisionBox::CollisionBox(int x, int y, int width, int height, bool activeStatus):
	TriggerZone(x,y,width,height,activeStatus)
{

}

void pushDrawableObjectOutsideCollisionBoxIfItIsIntersecting(DrawableObject& objectToPush) const
{
	int xAmountToCorrectLeftCollision = ((this->x)+((int)this->width) - objectToPush.getX());
	int xAmountToCorrectRightCollision = ((objectToPush.getX()+((int)objectToPush.getWidth()))-(this->x);
	int yAmountToCorrectTopCollision = ((this->y)+((int)this->height)) - objectToPush.getY());
	int yAmountToCorrectBottomCollision = ((objectToPush.getY()+((int)objectToPush.getHeight()))-(this->y));

	//Amount to corrects will be negative if there is no correction to be done and will be the positive amount to correct by if there is correction to be done.
	if(xAmountToCorrectLeftCollision < 0)
	{
		xAmountToCorrectLeftCollision = 0;
	}
	if(xAmountToCorrectRightCollision < 0)
	{
		xAmountToCorrectRightCollision = 0;
	}
	if(yAmountToCorrectTopCollision < 0)
	{
		yAmountToCorrectTopCollision = 0;
	}
	if(yAmountToCorrectBottomCollision < 0)
	{
		yAmountToCorrectBottomCollision = 0;
	}

	if(xAmountToCorrectLeftCollision < xAmountToCorrectRightCollision)
	{
		objectToPush.setX(objectToPush.getX() - xAmountToCorrectLeftCollision);
	}
	else
	{
		objectToPush.setX(objectToPush.getX() + xAmountToCorrectRightCollision);
	}

	if(yAmountToCorrectLeftCollision < yAmountToCorrectRightCollision)
	{
		objectToPush.setY(objectToPush.getY() - yAmountToCorrectTopCollision);
	}
	else
	{
		objectToPush.setY(objectToPush.getY() + yAmountToCorrectBottomCollision);
	}
}
