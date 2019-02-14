#pragma once
#ifdef _DEBUG
#define Debug
#endif //_DEBUG

#define IPSharedPtrExample

#ifdef IPSharedPtrExample
template <typename T>
class IPSharedPtr
{
public:
	explicit IPSharedPtr() : ptr_(nullptr), counter_(nullptr) {
#ifdef Debug
		std::cout << "constr def" << std::endl;
#endif //Debug
	};
	explicit IPSharedPtr(T* ptr) : ptr_(ptr), counter_(new unsigned int(1u)) {
#ifdef Debug
		std::cout << "constr def param" << std::endl;
#endif //Debug
	};
	explicit IPSharedPtr(const IPSharedPtr<T>& src)
	{
#ifdef Debug
		std::cout << "constr &" << std::endl;
#endif //Debug
		ptr_ = src.ptr_;
		//++(*src.counter_);
		counter_ = src.counter_;
		++(*counter_);
	}
	IPSharedPtr(IPSharedPtr&& src) noexcept : ptr_(src.ptr_), counter_(src.counter_)
	{
#ifdef Debug
		std::cout << "constr &&" << std::endl;
#endif //Debug
		src.ptr_ = nullptr;
		src.counter_ = nullptr;
	}

	~IPSharedPtr() {
#ifdef Debug
		std::cout << "~ def" << std::endl;
#endif //Debug
		if (--*counter_ == 0)
		{
			delete counter_;
			delete ptr_;
		}
	}

	T* getRawPtr() const noexcept { return ptr_; }
	unsigned int getRefsCount() const noexcept { return counter_; }

	IPSharedPtr& operator = (const IPSharedPtr<T>& src) noexcept
	{
#ifdef Debug
		std::cout << "oper =" << std::endl;
#endif //Debug
		ptr_ = src.ptr_;
		//++(*src.counter_);
		counter_ = src.counter_;
		++(*counter_);
		return *this;
	}
	IPSharedPtr& operator = (IPSharedPtr<T>&& src) noexcept
	{
#ifdef Debug
		std::cout << "oper ==" << std::endl;
#endif //Debug
		delete ptr_;
		delete counter_;
		ptr_ = src.ptr_;
		counter_ = src.counter_;

		src.ptr_ = nullptr;
		src.counter_ = nullptr;
		
		return *this;
	}

	T& operator*() const {
#ifdef Debug
		std::cout << "oper *" << std::endl;
#endif //Debug
		return *ptr_;
	}
	operator bool() const
	{
		return ptr_;
	}

private:
	unsigned int* counter_;
	T* ptr_;
};
#endif //IPSharedPtr
