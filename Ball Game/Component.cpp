#include "Component.h"

Component::Component(class Actor* actor, int order) : mOwner(actor), mUpdateOrder(order) {}

Component::~Component() {}

void Component::Update(float delta) {}