local entity = entities:createEntity()

local transform = TransformComponent(10, 200, 0)

entities:addComponent(entity, "TransformComponent", transform:get())

local getTransform = entities:getComponent(entity, "TransformComponent")
print(getTransform)
print(getTransform)