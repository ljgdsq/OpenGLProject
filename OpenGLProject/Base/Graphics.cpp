#include "Graphics.h"
#include "../Render/RenderTexture.h"
bool Graphics::isDepthEnable = false;
unsigned int Graphics::CurrentTarget = 0;

void Graphics::SetRenderTarget(RenderTexture* target)
{
    if (target) //�л�RT
    {
        auto targetN = target->framebuffer;

        if (targetN == CurrentTarget)
        {
            return;
        }
        
        if (CurrentTarget == 0) //��screen�л� ����depth����״̬
        {

            if (glIsEnabled(GL_DEPTH_TEST))
            {
                isDepthEnable = true;
            }
            else
            {
                isDepthEnable = false;
            }
        }

        glBindFramebuffer(GL_FRAMEBUFFER, targetN);
        target->Init();
        CurrentTarget = targetN;
    }
    else 
    {
        if (CurrentTarget==0)
        {
            return;
        }
        //��RT�л�
        if (isDepthEnable)
        {
            glEnable(GL_DEPTH_TEST);
        }
        else
        {
            glDisable(GL_DEPTH_TEST);
        }
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        CurrentTarget = 0;
    }
}
