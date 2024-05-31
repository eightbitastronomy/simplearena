# ARENA MEMORY MANAGEMENT

brought to you by cleverer people than me. But I did notice some limitations in the arena-implementation of stack-based memory allocation in C. In response, I wrote a very small and simple library: this one.

## "Okay my dude but what is arena memory?"

So glad you asked. I first encountered it with Rust, then discovered later that in C it can be a useful way to avoid the use of malloc and free. Malloc and free allocate and deallocate memory, respectively, from the heap. This must be done in C manually. Even meticulous developers can leave openings for memory leaks. In C++, the task is less burdensome, but there are those who have pointed out that heap usage in C++ can be less than straightforward (hence, memory leaks occur). Rust provides a novel way to avoid memory leaks, but the trade off is complexity. Now we come to stack-based memory. Every function call leads to resource-usage on the stack. One can't normally code a little "Hey just gimme some of that stack sh** so that I don't have to free it." Nonetheless, one doesn't always know the sizes of arrays and such at compile time. Hence, we're back at the heap, begging for forgiveness.

Arena memory is a stack-based solution. One declares a variable with a certain size, then writes routines that assign memory from that one variable. Since the variable is on the stack, when the variable goes out of scope, all of its memory is deallocated automatically. Here's some pseudocode:

function dosomething() {

ArenaMem mysandyspot;
string_ptr thistext;
string_ptr thattest;

thistext = call arena_allocator(size=32);
thattext = call arena_allocator(size=64);

stringfill(thistext, "This is end my friend");
stringfill(thattext, "So long and thanks for all the fish");

return;

}

And once the point of execution returns from dosomething(), mysandyspot vanishes from the stack, and with it, both thistext and thattext.

The implementation of arenas can involve some complex situations once concurrency is considered. This library doesn't touch on any of that. Instead, this library deals with one issue: if the arena variable has a size known at compile time, what happens if we don't have enough space for some arrays or something that we need?

One solution is to just recompile with larger arena sizes. Suppose for a moment that we aren't talking about an enterprise-sized suite where the mere scenario where a client discovers that the software ran out of memory would be really bad, or where the size of the suite prohibits recompilation. We might then choose arena sizes that are large enough for just about any situation. Modern 64-bit systems can handle this, having the wonders of virtual pages and swap spaces. Sure. But is this a practical way to code?

The solution presented here is wrapper functions. Each wrapper has a size in its name. One selects the most appropriate size and passes the function they want to use (target function) into the wrapper function. The wrapper function has an arena, and the address of this arena is passed into the target function. Inside the target function, one simply makes calls to the arena allocator. When the target function ends, there is no need for freeing, because the wrapper function will end immediately after, hence removing the arena from the stack.

Importantly, one still needs to know how big the arena should be. But with the wrapper functions, the developer can use small arenas here, big ones there, medium ones over here...you get the idea. Instead of asking for enormous 128 MB arenas at various points in the code, smaller asks can be made when smaller things need done.

## Usage

Your target function must be written with a variable-argument signature and must return an integer. For example, if your target function originally looked like...

int calculate_a_thing(int dims, double * vector3D, char * modifier, double ** output);

Then now it has to look like...

int calculate_a_thing(ArenaHolder aholder, va_list vl);  // variadic function pointer

And the wrapper call, with say 1024 bytes needed, would be...

retval = wrapper1K(calculate_a_thing, dims, vector3D, modifier, output);

Inside your NEW calculate_a_thing function, you must grab your function arguments using the usual va_args method, e.g.,

double ** localoutputvar = va_arg(vl, double **);

But, you don't need to use va_start or va_end. The wrapper does that. Then, make calls for allocation such as...

*localoutputvar = (double *)astake(aholder,sizeof(double)*dims);
int * myotherlocalarray = (int *)astake(aholder,sizeof(int)*someothervariable);
//and on and on

If you're arena isn't big enough, the astake returns NULL. Just like you would check to be sure malloc returned a non-null pointer, you would do that here too. There is nothing you can do a runtime if this happens. That's the downside to arenas. So, you'll need some kind of algorithm in your code for dynamically choosing the best wrapper function. For example, if you are building pixel maps of 4 8-bit channels, then you can predict the memory necessary with width x height x 4 bytes. Need three more of these for three layers to be flattened onto a fourth? Then multiply by four. Setup an if-then tree to scale up your wrapper size. Not too exciting, no, but if you're worried about memory leakage, then it's more exciting than tracing through your code.

Rock hard, ride [without using] free.

