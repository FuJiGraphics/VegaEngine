#include "pch.h"
#include "EntitySerializer.h"
#include "Entity.h"

namespace fz {

	EntitySerializer::EntitySerializer(const fz::Entity& entity)
		: m_Entity(entity)
		, m_EntityUUID(m_Entity.m_UUID)
	{
		// Empty
	}

	void EntitySerializer::Serialize(fz::json& json)
	{
		// Root Entity Á÷·ÄÈ­
		if (m_Entity.HasComponent<RootEntityComponent>())
			json[m_EntityUUID]["RootEntity"] = true;
		else
			json[m_EntityUUID]["RootEntity"] = false;

		if (m_Entity.HasComponent<ChildEntityComponent>())
		{
			json[m_EntityUUID]["HasChild"] = true;
			ChildEntityComponent& childComp = m_Entity.GetComponent<ChildEntityComponent>();
			for (auto& child : childComp.CurrentChildEntities)
			{
				ChildSerialize(json[m_Entity.m_UUID], child);
			}
		}
		else
		{
			json[m_EntityUUID]["HasChild"] = false;
		}

		this->SerializeTag(json[m_EntityUUID]);
		this->SerializeTransform(json[m_EntityUUID]);
		this->SerializeCamera(json[m_EntityUUID]);
		this->SerializeSprite(json[m_EntityUUID]);
	}

	void EntitySerializer::Deserialize(fz::json& json)
	{
		bool isRootEntity = json[m_EntityUUID]["RootEntity"];
		bool hasChild = json[m_EntityUUID]["HasChild"];

		if (isRootEntity)
		{
			auto& rootEntityComp = m_Entity.AddComponent<RootEntityComponent>();
			rootEntityComp.RootEntity = m_Entity;
		}
		for (auto it = json[m_EntityUUID].begin(); it != json[m_EntityUUID].end(); ++it)
		{
			const std::string& component = it.key();
			if (component == "TagComponent")
				this->DeserializeTag(json[m_EntityUUID]);
			else if (component == "TransformComponent")
				this->DeserializeTransform(json[m_EntityUUID]);
			else if (component == "CameraComponent")
				this->DeserializeCamera(json[m_EntityUUID]);
			else if (component == "SpriteComponent")
				this->DeserializeSprite(json[m_EntityUUID]);
			else if (component == "RootEntity")
				isRootEntity = json[m_EntityUUID]["RootEntity"];
			else if (component == "HasChild")
				hasChild = json[m_EntityUUID]["HasChild"];
			else if (hasChild)
			{
				fz::Entity entity = m_Entity.CreateChildEntity(component, "New Child Entity...");
				this->ChildDerialize(json[m_EntityUUID], entity);
			}
		}
	}

	void EntitySerializer::ChildSerialize(fz::json& json, fz::Entity& child)
	{
		EntitySerializer serializer(child);
		serializer.Serialize(json);
	}

	void EntitySerializer::ChildDerialize(fz::json& json, fz::Entity& child)
	{
		EntitySerializer serializer(child);
		serializer.Deserialize(json);
	}

	void EntitySerializer::SerializeTag(json& json)
	{
		if (m_Entity.HasComponent<TagComponent>())
		{
			const auto& tag = m_Entity.GetComponent<TagComponent>();
			const auto& tagName = tag.Tag;
			json["TagComponent"]["Tag"] = tagName;
		}
	}

	void EntitySerializer::SerializeCamera(json& json)
	{
		if (m_Entity.HasComponent<CameraComponent>())
		{
			const auto& cameraComp = m_Entity.GetComponent<CameraComponent>();
			const auto& camera = m_Entity.GetComponent<CameraComponent>().Camera;
			json["CameraComponent"]["FixedAspectRatio"] = cameraComp.FixedAspectRatio;
			json["CameraComponent"]["Primary"] = cameraComp.Primary;
			json["CameraComponent"]["Center"] = { camera.GetCenter().x, camera.GetCenter().y };
			json["CameraComponent"]["Size"] = { camera.GetSize().x, camera.GetSize().y };
			json["CameraComponent"]["Rotation"] = camera.GetRotation();
			json["CameraComponent"]["Zoom"] = camera.GetZoom();
			json["CameraComponent"]["Viewport"]["Left"] = camera.GetViewport().left;
			json["CameraComponent"]["Viewport"]["Top"] = camera.GetViewport().top;
			json["CameraComponent"]["Viewport"]["Width"] = camera.GetViewport().width;
			json["CameraComponent"]["Viewport"]["Height"] = camera.GetViewport().height;
		}
	}

	void EntitySerializer::SerializeTransform(json& json)
	{
		if (m_Entity.HasComponent<TransformComponent>())
		{
			const auto& transform = m_Entity.GetComponent<TransformComponent>().Transform;
			const auto& translate = transform.GetTranslate();
			const auto& scale = transform.GetScale();
			const auto& rotation = transform.GetRotation();
			const auto& origin = transform.GetOrigin();
			json["TransformComponent"]["Translate"] = { translate.x, translate.y };
			json["TransformComponent"]["Rotation"] = rotation;
			json["TransformComponent"]["Scale"] = { scale.x, scale.y };
			json["TransformComponent"]["Origin"] = { origin.x, origin.y };
		}
	}

	void EntitySerializer::SerializeSprite(json& json)
	{
		if (m_Entity.HasComponent<SpriteComponent>())
		{
			auto& spriteComp = m_Entity.GetComponent<SpriteComponent>();
			auto& sprite = spriteComp.Sprite;
			const auto& texPath = sprite.GetTexturePath();
			sf::Sprite& rawSprite = sprite;
			const auto& texRect = sprite.GetTextureRect();
			const auto& color = rawSprite.getColor();
			const auto& maskColor = sprite.GetMaskColor();
			json["SpriteComponent"]["TexPath"] = texPath;
			json["SpriteComponent"]["TexRect"]["Left"] = texRect.left;
			json["SpriteComponent"]["TexRect"]["Top"] = texRect.top;
			json["SpriteComponent"]["TexRect"]["Width"] = texRect.width;
			json["SpriteComponent"]["TexRect"]["Height"] = texRect.height;
			json["SpriteComponent"]["Color"]["R"] = color.r;
			json["SpriteComponent"]["Color"]["G"] = color.g;
			json["SpriteComponent"]["Color"]["B"] = color.b;
			json["SpriteComponent"]["Color"]["A"] = color.a;
			json["SpriteComponent"]["Position"] = { rawSprite.getPosition().x, rawSprite.getPosition().y };
			json["SpriteComponent"]["Scale"] = { rawSprite.getScale().x, rawSprite.getScale().y };
			json["SpriteComponent"]["Rotation"] = rawSprite.getRotation();
			json["SpriteComponent"]["Origin"] = { rawSprite.getOrigin().x, rawSprite.getOrigin().y };
			json["SpriteComponent"]["Origins"] = Converter::ToString(sprite.GetOrigins());
			json["SpriteComponent"]["MaskMode"] = sprite.IsMaskMode();
			json["SpriteComponent"]["MaskColor"]["R"] = maskColor.r;
			json["SpriteComponent"]["MaskColor"]["G"] = maskColor.g;
			json["SpriteComponent"]["MaskColor"]["B"] = maskColor.b;
			json["SpriteComponent"]["MaskColor"]["A"] = maskColor.a;
			json["SpriteComponent"]["SortingOrder"] = spriteComp.SortingOrder;
		}
	}

	void EntitySerializer::DeserializeTag(json& json)
	{
		TagComponent& tagComp = FindComponent<TagComponent>();
		tagComp.Tag = json["TagComponent"]["Tag"];
	}

	void EntitySerializer::DeserializeCamera(json& json)
	{
		CameraComponent& cameraComp = FindComponent<CameraComponent>();
		cameraComp.FixedAspectRatio = json["CameraComponent"]["FixedAspectRatio"];
		cameraComp.Primary = json["CameraComponent"]["Primary"];

		std::vector<float> centorPos = json["CameraComponent"]["Center"];
		std::vector<float> size = json["CameraComponent"]["Size"];
		float rotation = json["CameraComponent"]["Rotation"];
		float zoom = json["CameraComponent"]["Zoom"];
		float left = json["CameraComponent"]["Viewport"]["Left"];
		float top = json["CameraComponent"]["Viewport"]["Top"];
		float width = json["CameraComponent"]["Viewport"]["Width"];
		float height = json["CameraComponent"]["Viewport"]["Height"];

		auto& camera = cameraComp.Camera;
		camera.SetCenter(centorPos[0], centorPos[1]);
		camera.SetSize(size[0], size[1]);
		camera.SetRotation(rotation);
		camera.Zoom(zoom);
		camera.SetViewport({ left, top, width, height });
	}

	void EntitySerializer::DeserializeTransform(json& json)
	{
		TransformComponent& transfomComp = FindComponent<TransformComponent>();
		auto& transform = transfomComp.Transform;

		std::vector<float> translate = json["TransformComponent"]["Translate"];
		std::vector<float> scale =  json["TransformComponent"]["Scale"];
		float rotation = json["TransformComponent"]["Rotation"];
		std::vector<float> origin = json["TransformComponent"]["Origin"];

		transform.SetTranslate(translate[0], translate[1]);
		transform.SetScale(scale[0], scale[1]);
		transform.SetRotation(rotation);
		transform.SetOrigin(origin[0], origin[1]);
	}

	void EntitySerializer::DeserializeSprite(json& json)
	{
		SpriteComponent& spriteComp = FindComponent<SpriteComponent>();
		auto& sprite = spriteComp.Sprite;

		std::string texPath = json["SpriteComponent"]["TexPath"];
		sprite.SetTexture(texPath);

		sf::Sprite& rawSprite = sprite;

		// Get SortingOrder
		spriteComp.SortingOrder = json["SpriteComponent"]["SortingOrder"];

		// Get MaskColor
		bool maskMode = json["SpriteComponent"]["MaskMode"];
		sf::Uint8 mr = json["SpriteComponent"]["MaskColor"]["R"];
		sf::Uint8 mg = json["SpriteComponent"]["MaskColor"]["G"];
		sf::Uint8 mb = json["SpriteComponent"]["MaskColor"]["B"];
		sf::Uint8 ma = json["SpriteComponent"]["MaskColor"]["A"];
		sprite.SetMaskColor(maskMode, { mr, mg, mb, ma });

		sf::Uint8 r = json["SpriteComponent"]["Color"]["R"];
		sf::Uint8 g = json["SpriteComponent"]["Color"]["G"];
		sf::Uint8 b = json["SpriteComponent"]["Color"]["B"];
		sf::Uint8 a = json["SpriteComponent"]["Color"]["A"];
		rawSprite.setColor({ r, g, b, a });

		std::vector<float> pos = json["SpriteComponent"]["Position"];
		std::vector<float> scale = json["SpriteComponent"]["Scale"];
		float rotation = json["SpriteComponent"]["Rotation"];
		std::vector<float> origin = json["SpriteComponent"]["Origin"];
		std::string originsStr = json["SpriteComponent"]["Origins"];
		Origins origins = Converter::StringToOrigins(originsStr);

		int left = json["SpriteComponent"]["TexRect"]["Left"];
		int top = json["SpriteComponent"]["TexRect"]["Top"];
		int width = json["SpriteComponent"]["TexRect"]["Width"];
		int height = json["SpriteComponent"]["TexRect"]["Height"];
		sprite.SetTextureRect({ left, top, width, height });
		rawSprite.setPosition(pos[0], pos[1]);
		rawSprite.setScale(scale[0], scale[1]);
		rawSprite.setRotation(rotation);
		if (origins == Origins::Custom)
			rawSprite.setOrigin(origin[0], origin[1]);
		else
			sprite.SetOrigins(origins);
	}

} // namespace fz
