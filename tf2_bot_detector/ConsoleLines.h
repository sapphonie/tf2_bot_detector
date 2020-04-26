#pragma once

#include "LobbyMember.h"

#include <memory>
#include <string_view>

namespace tf2_bot_detector
{
	enum class ConsoleLineType
	{
		Generic,
		Chat,
		LobbyHeader,
		LobbyMember,
	};

	class IConsoleLine
	{
	public:
		virtual ~IConsoleLine() = default;

		virtual ConsoleLineType GetType() const = 0;
		virtual void Print() const = 0;

		static std::unique_ptr<IConsoleLine> ParseConsoleLine(const std::string_view& text);
	};

	class GenericConsoleLine final : public IConsoleLine
	{
	public:
		GenericConsoleLine(std::string&& text);

		ConsoleLineType GetType() const override { return ConsoleLineType::Generic; }
		void Print() const override;

	private:
		std::string m_Text;
	};

	class ChatConsoleLine final : public IConsoleLine
	{
	public:
		ChatConsoleLine(std::string&& playerName, std::string&& message, bool isDead, bool isTeam);

		ConsoleLineType GetType() const override { return ConsoleLineType::Chat; }
		void Print() const override;

	private:
		std::string m_PlayerName;
		std::string m_Message;
		bool m_IsDead : 1;
		bool m_IsTeam : 1;
	};

	class LobbyHeaderLine final : public IConsoleLine
	{
	public:
		LobbyHeaderLine(unsigned memberCount, unsigned pendingCount);

		auto GetMemberCount() const { return m_MemberCount; }
		auto GetPendingCount() const { return m_PendingCount; }

		ConsoleLineType GetType() const override { return ConsoleLineType::LobbyHeader; }
		void Print() const override;

	private:
		unsigned m_MemberCount;
		unsigned m_PendingCount;
	};

	class LobbyMemberLine final : public IConsoleLine
	{
	public:

		LobbyMemberLine(const LobbyMember& lobbyMember);

		const LobbyMember& GetLobbyMember() const { return m_LobbyMember; }

		ConsoleLineType GetType() const { return ConsoleLineType::LobbyMember; }
		void Print() const override;

	private:
		LobbyMember m_LobbyMember;
	};
}