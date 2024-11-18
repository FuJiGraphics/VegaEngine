#include "pch.h"
#include "EntitySerializer.h"
#include "Entity.h"

namespace fz {

	EntitySerializer::EntitySerializer(const std::string& sceneUUID, const fz::Entity& entity)
		: m_Entity(entity)
		, m_SceneUUID(sceneUUID)
	{
		// Empty
	}

	void EntitySerializer::Serialize(const std::string& path)
	{
		auto& json = Database::GetJsonObject(path);

		m_EntityUUID = m_Entity.m_UUID;

		this->SerializeTag(json);
		this->SerializeTransform(json);
		this->SerializeCamera(json);
		this->SerializeSprite(json);
	}

	void EntitySerializer::Deserialize(const std::string& path)
	{
		auto& json = Database::GetJsonObject(path);

		m_EntityUUID = m_Entity.m_UUID;

		for (json::iterator itComponent = json[m_SceneUUID][m_EntityUUID].begin(); 
			 itComponent != json[m_SceneUUID][m_EntityUUID].end(); ++itComponent)
		{
			const std::string& component = itComponent.key();
			if (component == "TagComponent")
				this->DeserializeTag(json);
			else if (component == "TransformComponent")
				this->DeserializeTransform(json);
			else if (component == "CameraComponent")
				this->DeserializeCamera(json);
			else if (component == "SpriteComponent")
				this->DeserializeSprite(json);
		}
	}

	void EntitySerializer::SerializeTag(json& json)
	{
		if (m_Entity.HasComponent<TagComponent>())
		{
			const auto& tag = m_Entity.GetComponent<TagComponent>();
			const auto& tagName = tag.Tag;
			json[m_SceneUUID][m_EntityUUID]["TagComponent"]["Tag"] = tagName;
		}
	}

	void EntitySerializer::SerializeCamera(json& json)
	{
		if (m_Entity.HasComponent<CameraComponent>())
		{
			const auto& cameraComp = m_Entity.GetComponent<CameraComponent>();
			json[m_SceneUUID][m_EntityUUID]["CameraComponent"]["FixedAspectRatio"] = cameraComp.FixedAspectRatio;
			json[m_SceneUUID][m_EntityUUID]["CameraComponent"]["Primary"] = cameraComp.Primary;
			const auto& camera = m_Entity.GetComponent<CameraComponent>().Camera;
			json[m_SceneUUID][m_EntityUUID]["CameraComponent"]["Center"] = { camera.GetCenter().x, camera.GetCenter().y };
			json[m_SceneUUID][m_EntityUUID]["CameraComponent"]["Size"] = { camera.GetSize().x, camera.GetSize().y };
			json[m_SceneUUID][m_EntityUUID]["CameraComponent"]["Rotation"] = camera.GetRotation();
			json[m_SceneUUID][m_EntityUUID]["CameraComponent"]["Zoom"] = camera.GetZoom();
			json[m_SceneUUID][m_EntityUUID]["CameraComponent"]["Viewport"]["Left"] = camera.GetViewport().left;
			json[m_SceneUUID][m_EntityUUID]["CameraComponent"]["Viewport"]["Top"] = camera.GetViewport().top;
			json[m_SceneUUID][m_EntityUUID]["CameraComponent"]["Viewport"]["Width"] = camera.GetViewport().width;
			json[m_SceneUUID][m_EntityUUID]["CameraComponent"]["Viewport"]["Height"] = camera.GetViewport().height;
		}
	}

	void EntitySerializer::SerializeTransform(json& json)
	{
		if (m_Entity.HasComponent<TransformComponent>())
		{
			const auto& transform = m_Entity.GetComponent<TransformComponent>().Transform;
			const auto& translate = transform.GetTranslate();
			json[m_SceneUUID][m_EntityUUID]["TransformComponent"]["Translate"] = { translate.x, translate.y };
			const auto& scale = transform.GetScale();
			json[m_SceneUUID][m_EntityUUID]["TransformComponent"]["Scale"] = { scale.x, scale.y };
			const auto& rotation = transform.GetRotation();
			json[m_SceneUUID][m_EntityUUID]["TransformComponent"]["Rotation"] = rotation;
			const auto& origin = transform.GetOrigin();
			json[m_SceneUUID][m_EntityUUID]["TransformComponent"]["Origin"] = { origin.x, origin.y };
		}
	}

	void EntitySerializer::SerializeSprite(json& json)
	{
		if (m_Entity.HasComponent<SpriteComponent>())
		{
			auto& sprite = m_Entity.GetComponent<SpriteComponent>().Sprite;
			const auto& texPath = sprite.GetTexturePath();
			json[m_SceneUUID][m_EntityUUID]["SpriteComponent"]["TexPath"] = texPath;
			sf::Sprite& rawSprite = sprite;
			const auto& texRect = sprite.GetTextureRect();
			const auto& color = rawSprite.getColor();
			const auto& maskColor = sprite.GetMaskColor();
			json[m_SceneUUID][m_EntityUUID]["SpriteComponent"]["TexRect"]["Left"] = texRect.left;
			json[m_SceneUUID][m_EntityUUID]["SpriteComponent"]["TexRect"]["Top"] = texRect.top;
			json[m_SceneUUID][m_EntityUUID]["SpriteComponent"]["TexRect"]["Width"] = texRect.width;
			json[m_SceneUUID][m_EntityUUID]["SpriteComponent"]["TexRect"]["Height"] = texRect.height;
			json[m_SceneUUID][m_EntityUUID]["SpriteComponent"]["Color"]["R"] = color.r;
			json[m_SceneUUID][m_EntityUUID]["SpriteComponent"]["Color"]["G"] = color.g;
			json[m_SceneUUID][m_EntityUUID]["SpriteComponent"]["Color"]["B"] = color.b;
			json[m_SceneUUID][m_EntityUUID]["SpriteComponent"]["Color"]["A"] = color.a;
			json[m_SceneUUID][m_EntityUUID]["SpriteComponent"]["Position"] = { rawSprite.getPosition().x, rawSprite.getPosition().y };
			json[m_SceneUUID][m_EntityUUID]["SpriteComponent"]["Scale"]	= { rawSprite.getScale().x, rawSprite.getScale().y };
			json[m_SceneUUID][m_EntityUUID]["SpriteComponent"]["Rotation"] = rawSprite.getRotation();
			json[m_SceneUUID][m_EntityUUID]["SpriteComponent"]["Origin"] = { rawSprite.getOrigin().x, rawSprite.getOrigin().y };
			json[m_SceneUUID][m_EntityUUID]["SpriteComponent"]["Origins"] = Converter::ToString(sprite.GetOrigins());
			json[m_SceneUUID][m_EntityUUID]["SpriteComponent"]["MaskMode"] = sprite.IsMaskMode();
			json[m_SceneUUID][m_EntityUUID]["SpriteComponent"]["MaskColor"]["R"] = maskColor.r;
			json[m_SceneUUID][m_EntityUUID]["SpriteComponent"]["MaskColor"]["G"] = maskColor.g;
			json[m_SceneUUID][m_EntityUUID]["SpriteComponent"]["MaskColor"]["B"] = maskColor.b;
			json[m_SceneUUID][m_EntityUUID]["SpriteComponent"]["MaskColor"]["A"] = maskColor.a;
		}
	}

	void EntitySerializer::DeserializeTag(json& json)
	{
		TagComponent& tagComp = FindComponent<TagComponent>();
		tagComp.Tag = json[m_SceneUUID][m_EntityUUID]["TagComponent"]["Tag"];
	}

	void EntitySerializer::DeserializeCamera(json& json)
	{
		CameraComponent& cameraComp = FindComponent<CameraComponent>();
		cameraComp.FixedAspectRatio = json[m_SceneUUID][m_EntityUUID]["CameraComponent"]["FixedAspectRatio"];
		cameraComp.Primary = json[m_SceneUUID][m_EntityUUID]["CameraComponent"]["Primary"];

		std::vector<float> centorPos = json[m_SceneUUID][m_EntityUUID]["CameraComponent"]["Center"];
		std::vector<float> size = json[m_SceneUUID][m_EntityUUID]["CameraComponent"]["Size"];
		float rotation = json[m_SceneUUID][m_EntityUUID]["CameraComponent"]["Rotation"];
		float zoom = json[m_SceneUUID][m_EntityUUID]["CameraComponent"]["Zoom"];
		float left = json[m_SceneUUID][m_EntityUUID]["CameraComponent"]["Viewport"]["Left"];
		float top = json[m_SceneUUID][m_EntityUUID]["CameraComponent"]["Viewport"]["Top"];
		float width = json[m_SceneUUID][m_EntityUUID]["CameraComponent"]["Viewport"]["Width"];
		float height = json[m_SceneUUID][m_EntityUUID]["CameraComponent"]["Viewport"]["Height"];

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

		std::vector<float> translate = json[m_SceneUUID][m_EntityUUID]["TransformComponent"]["Translate"];
		std::vector<float> scale =  json[m_SceneUUID][m_EntityUUID]["TransformComponent"]["Scale"];
		float rotation = json[m_SceneUUID][m_EntityUUID]["TransformComponent"]["Rotation"];
		std::vector<float> origin = json[m_SceneUUID][m_EntityUUID]["TransformComponent"]["Origin"];

		transform.SetTranslate(translate[0], translate[1]);
		transform.SetScale(scale[0], scale[1]);
		transform.SetRotation(rotation);
		transform.SetOrigin(origin[0], origin[1]);
	}

	void EntitySerializer::DeserializeSprite(json& json)
	{
		SpriteComponent& spriteComp = FindComponent<SpriteComponent>();
		auto& sprite = spriteComp.Sprite;

		std::string texPath = json[m_SceneUUID][m_EntityUUID]["SpriteComponent"]["TexPath"];
		sprite.SetTexture(texPath);

		sf::Sprite& rawSprite = sprite;

		// Get MaskColor
		bool maskMode = json[m_SceneUUID][m_EntityUUID]["SpriteComponent"]["MaskMode"];
		sf::Uint8 mr = json[m_SceneUUID][m_EntityUUID]["SpriteComponent"]["MaskColor"]["R"];
		sf::Uint8 mg = json[m_SceneUUID][m_EntityUUID]["SpriteComponent"]["MaskColor"]["G"];
		sf::Uint8 mb = json[m_SceneUUID][m_EntityUUID]["SpriteComponent"]["MaskColor"]["B"];
		sf::Uint8 ma = json[m_SceneUUID][m_EntityUUID]["SpriteComponent"]["MaskColor"]["A"];
		sprite.SetMaskColor(maskMode, { mr, mg, mb, ma });

		sf::Uint8 r = json[m_SceneUUID][m_EntityUUID]["SpriteComponent"]["Color"]["R"];
		sf::Uint8 g = json[m_SceneUUID][m_EntityUUID]["SpriteComponent"]["Color"]["G"];
		sf::Uint8 b = json[m_SceneUUID][m_EntityUUID]["SpriteComponent"]["Color"]["B"];
		sf::Uint8 a = json[m_SceneUUID][m_EntityUUID]["SpriteComponent"]["Color"]["A"];
		rawSprite.setColor({ r, g, b, a });

		std::vector<float> pos = json[m_SceneUUID][m_EntityUUID]["SpriteComponent"]["Position"];
		std::vector<float> scale = json[m_SceneUUID][m_EntityUUID]["SpriteComponent"]["Scale"];
		float rotation = json[m_SceneUUID][m_EntityUUID]["SpriteComponent"]["Rotation"];
		std::vector<float> origin = json[m_SceneUUID][m_EntityUUID]["SpriteComponent"]["Origin"];
		std::string originsStr = json[m_SceneUUID][m_EntityUUID]["SpriteComponent"]["Origins"];
		Origins origins = Converter::StringToOrigins(originsStr);
		rawSprite.setPosition(pos[0], pos[1]);
		rawSprite.setScale(scale[0], scale[1]);
		rawSprite.setRotation(rotation);
		rawSprite.setOrigin(origin[0], origin[1]);
		sprite.SetOrigins(origins);

		int left = json[m_SceneUUID][m_EntityUUID]["SpriteComponent"]["TexRect"]["Left"];
		int top = json[m_SceneUUID][m_EntityUUID]["SpriteComponent"]["TexRect"]["Top"];
		int width = json[m_SceneUUID][m_EntityUUID]["SpriteComponent"]["TexRect"]["Width"];
		int height = json[m_SceneUUID][m_EntityUUID]["SpriteComponent"]["TexRect"]["Height"];
		sprite.SetTextureRect({ left, top, width, height });
	}

} // namespace fz
