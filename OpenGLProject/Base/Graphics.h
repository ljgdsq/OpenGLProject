#pragma once
class Graphics
{
private:
    Graphics() = delete;
    Graphics(const Graphics&) = delete;
    Graphics(const Graphics&&) = delete;
public:
    static void SetRenderTarget(class RenderTexture*target);

private:
    static bool isDepthEnable;
    static unsigned int CurrentTarget;
};

