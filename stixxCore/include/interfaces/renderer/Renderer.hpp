#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <chrono>
#include "utils/Observer.hpp"

namespace sx
{
	class HotLoopObserver
		: public Observer<HotLoopObserver>
	{
	public:
		using Observer<HotLoopObserver>::Observer;
		virtual void Update(std::chrono::duration<float>& elapsedMs) = 0;
	};

	class Renderer
		: public Subject<HotLoopObserver>
	{
	public:
		virtual ~Renderer(){};
		virtual void Draw()  = 0;
	};

	class Buffer;

	enum BufferType
	{
		TransferSrc = 0x1,
		Indices = 0x40,
		VertexData = 0x80
	};

	class  GPUMemoryLoader
	{
	public:
		virtual ~GPUMemoryLoader() {};
		virtual uint32_t Alignment() const = 0;
		virtual void LoadDataToMemory(const BufferType type, const std::size_t size, std::function<void(void*)>& WriteAvailable, std::function<void(Buffer)>& onDone) const = 0;
	};
}

#endif
