local entity = entities:createEntity()

local transform = TransformComponent(10, 200, 0)

entities:addComponent(entity, "TransformComponent", transform:get())

local sprite = CubeSpriteComponent(200, 200, 0, 255)

entities:addComponent(entity, "CubeSpriteComponent", sprite:get())

local getTransform = entities:getComponent(entity, "TransformComponent")
print(getTransform)
print(getTransform)