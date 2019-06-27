// ----------------------------------------------------------------------------
#pragma region// ASSIGNMENT 2


// Simple model class
struct Model
{
	Vector2*	mVertexArray;
	u32			mVertexCount;
	Model() : mVertexArray(0), mVertexCount(0)
	{}
};

// creates a quad in the given model
void MakeQuad(Model * model);
void MakeCircle(Model * model);
void MakeCross(Model * model);

// copy a model
void CopyModel(Model * srcModel, Model * dstModel);

// Draws a model in the given color
void DrawModel(Model *  model, unsigned color);

// Transform inVertices by transform and stores the result in outVertices. Both arrays are assumed to be of size count
void TransformModel(Model * inModel, Model * outModel, const Transform2D & transform);

// frees the vertex memory of a given quad
void FreeModel(Model * model);

#pragma endregion
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
#pragma region// ASSIGNMENT 3

struct RigidBody;
RigidBody* CreateRandBoxWithMass(f32 mass, Vector2 gravity);
RigidBody* CreateRandCircleWithMass(f32 mass, Vector2 gravity);

#pragma endregion
// ----------------------------------------------------------------------------

void GameFlow();