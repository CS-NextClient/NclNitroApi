#pragma once

#include <nitroapi/hook/GenericHookInterface.h>
#include "nitroapi/chain/Unsubscriber.h"
#include <nitroapi/chain/HandlersChainBaseInterface.h>
#include <nitroapi/chain/HandlersChainInterface.h>
#include <functional>

namespace nitroapi
{
    template<class TResult, class... TArgs>
    class HandlersChain : public HandlersChainInterface<TResult, TArgs...>
    {
        class NextHandler : public NextHandlerInterface<TResult, TArgs...>
        {
            std::function<TResult(TArgs...)> callback_;

        public:
            TResult Invoke(TArgs... args) override
            {
                return callback_(std::forward<TArgs>(args)...);
            }

            void SetCallback(const std::function<TResult(TArgs...)>& callback)
            {
                callback_ = callback;
            }
        };

        template<class T, class Dummy_AvoidGccBug = void>
        struct GenericHookHelper {
            static void SetHook(HandlersChain<TResult, TArgs...>* chain, GenericHookInterface<TResult, TArgs...>* hook)
            {
                hook->SetCallbackAndEnableHook([chain](TArgs... args) -> TResult
                                               { return GenericHook(chain, std::forward<TArgs>(args)...); });
            }

            static TResult GenericHook(HandlersChain<TResult, TArgs...>* chain, TArgs... args)
            {
                TResult result;

                auto it = chain->handlers_.cbegin();

                NextHandler next_handler;
                std::function<TResult(TArgs...)> next = [chain, &it, &next, &next_handler](TArgs... a) -> TResult
                {
                    if (it == chain->handlers_.cend())
                        return chain->hook_->InvokeOriginal(std::forward<TArgs>(a)...);

                    auto it_cur = it++;
                    return (*it_cur)->Handle(std::forward<TArgs>(a)..., &next_handler);
                };
                next_handler.SetCallback(next);
                result = next_handler.Invoke(std::forward<TArgs>(args)...);

                for (int i = chain->subscribers_.size() - 1; i >= 0; i--)
                {
                    auto& subscriber = chain->subscribers_[i];
                    subscriber->OnEvent(std::forward<TArgs>(args)..., result);
                }

                return result;
            }
        };

        template<class Dummy_AvoidGccBug>
        struct GenericHookHelper<void, Dummy_AvoidGccBug> {
            static void SetHook(HandlersChain<TResult, TArgs...>* chain, GenericHookInterface<TResult, TArgs...>* hook)
            {
                hook->SetCallbackAndEnableHook([chain](TArgs... args)
                                               { GenericHook(chain, std::forward<TArgs>(args)...); });
            }

            static void GenericHook(HandlersChain<TResult, TArgs...>* chain, TArgs... args)
            {
                auto it = chain->handlers_.cbegin();

                NextHandler next_handler;
                std::function<void(TArgs...)> next = [chain, &it, &next, &next_handler](TArgs... a)
                {
                    if (it == chain->handlers_.cend())
                    {
                        chain->hook_->InvokeOriginal(std::forward<TArgs>(a)...);
                        return;
                    }

                    auto it_cur = it++;
                    (*it_cur)->Handle(std::forward<TArgs>(a)..., &next_handler);
                };
                next_handler.SetCallback(next);
                next_handler.Invoke(std::forward<TArgs>(args)...);

                for (int i = chain->subscribers_.size() - 1; i >= 0; i--)
                {
                    auto& subscriber = chain->subscribers_[i];
                    subscriber->OnEvent(std::forward<TArgs>(args)..., VoidResult{});
                }
            }
        };

        std::vector<HandlerInterface<TResult, TArgs...>*> handlers_;
        std::vector<SubscriberInterface<TResult, TArgs...>*> subscribers_;

        GenericHookInterface<TResult, TArgs...>* hook_ = nullptr;

    public:
        HandlersChain() = default;
        ~HandlersChain() override = default;

        void AttachHook(GenericHookInterface<TResult, TArgs...>* hook) override
        {
            DetachHook();

            hook_ = hook;
            GenericHookHelper<TResult>::SetHook(this, hook_);
        }

        void DetachHook() override
        {
            if (hook_ == nullptr)
                return;

            hook_->UnsetCallbackAndDisableHook();
            hook_ = nullptr;
        }

        [[nodiscard]] bool IsHookAttached() override
        {
            return hook_ != nullptr;
        }

        [[nodiscard]] GenericHookInterface<TResult, TArgs...>* GetHook() const override
        {
            return hook_;
        }

        [[nodiscard]] uint32_t GetSubscribersCount() const override
        {
            return subscribers_.size();
        }

        [[nodiscard]] uint32_t GetHandlersCount() const override
        {
            return handlers_.size();
        }

        bool AddHandler(HandlerInterface<TResult, TArgs...>* handler) override
        {
            auto result = std::find(handlers_.begin(), handlers_.end(), handler);
            if (result != std::end(handlers_))
                return false;

            handlers_.push_back(handler);
            return true;
        }

        bool RemoveHandler(HandlerInterface<TResult, TArgs...>* handler) override
        {
            auto result = std::find(handlers_.begin(), handlers_.end(), handler);
            if (result == std::end(handlers_))
                return false;

            handlers_.erase(result);
            return true;
        }

        bool Subscribe(SubscriberInterface<TResult, TArgs...>* subscriber) override
        {
            auto result = std::find(subscribers_.begin(), subscribers_.end(), subscriber);
            if (result != std::end(subscribers_))
                return false;

            subscribers_.push_back(subscriber);
            return true;
        }

        bool Unsubscribe(SubscriberInterface<TResult, TArgs...>* subscriber) override
        {
            auto result = std::find(subscribers_.begin(), subscribers_.end(), subscriber);
            if (result == std::end(subscribers_))
                return false;

            subscribers_.erase(result);
            return true;
        }
    };
}