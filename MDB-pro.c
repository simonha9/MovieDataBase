#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_STR_LEN 1024

/* Compound data type declarations */
/***************************************************************************/
/******                         TO DO                               ********/
/****** In the space below, complete the definitions of the compound *******/
/****** data types that will be needed to implement the movie review *******/
/****** linked list. This includes the MovieReview type, and the     *******/
/****** ReviewNode. Details about the contents of these can be       *******/
/****** found in the assignment handout. Read them carefully!        *******/
/***************************************************************************/

typedef struct ScoreNode_struct {
  int score;
  struct ScoreNode_struct *next;
} ScoreNode;

ScoreNode *newScoreNode() {
  ScoreNode *new_score = NULL;
  new_score = (ScoreNode*)calloc(1, sizeof(ScoreNode));

  new_score->score = -1;
  new_score->next = NULL;
  return new_score;
}



typedef struct MovieReview_struct
{
  char movie_title[MAX_STR_LEN];
  char movie_studio[MAX_STR_LEN];
  int year;
  float BO_total;
  ScoreNode *scores_head;
} Movie_Review;

typedef struct ReviewNode_struct
{
  Movie_Review review;
  struct ReviewNode_struct *next;
} ReviewNode;

ScoreNode *insertNewScore(ScoreNode *scores_head, int score) {
  /* Takes score and inserts it at the head of the scores linkdlist
  * Returns the head of the linkdlist */
  ScoreNode *p = NULL;
  p = newScoreNode();

  p->score = score;
  p->next = scores_head;
  return p;
}

ReviewNode *newMovieReviewNode()
{
    /*
     * This function allocates a new, empty ReviewNode, and initializes the
     * contents of the MovieReview for this node to empty values.
     * The fields in the MovieReview should be set to:
     *  movie_title=""
     *  movie_studio=""
     *  year = -1
     *  BO_total = -1
     *  score = -1
     *
     * The *next pointer for the new node MUST be set to NULL
     *
     * The function must return a pointer to the newly allocated and initialized
     * node. If something goes wrong, the function returns NULL
     */

    /***************************************************************************/
    /**********  TO DO: Complete this function *********************************/
    /***************************************************************************/

    ReviewNode *new_review = NULL;
    new_review = (ReviewNode *)calloc(1, sizeof(ReviewNode));

    strcpy(new_review->review.movie_title, "");
    strcpy(new_review->review.movie_studio, "");
    new_review->review.year = -1;
    new_review->review.BO_total = -1;
    new_review->review.scores_head = NULL;
    new_review->next = NULL;

    return new_review;	// <--- This should change when after you implement your solution
}

ReviewNode *findMovieReview(const char title[MAX_STR_LEN], const char studio[MAX_STR_LEN], int year, ReviewNode *head)
{
    /*
     * This function searches through the linked list for a review that matches the input query.
     * In this case, the movie review must match the title, studio, and year provided in the
     * parameters for this function.
     *
     * If a review matching the query is found, this function returns a pointer to the node that
     * contains that review.
     *
     * If no such review is found, this function returns NULL
     */

    /***************************************************************************/
    /**********  TO DO: Complete this function *********************************/
    /***************************************************************************/
    ReviewNode *p = head; // Traversal Node

    while (p != NULL) {
      if ((strcmp(p->review.movie_title, title) == 0) && (strcmp(p->review.movie_studio, studio) == 0) && \
      (p->review.year == year)) {
        return p;
      }
      p = p->next;
    }
    return NULL;	// <--- This should change when after you implement your solution
}

ReviewNode *insertMovieReview(const char title[MAX_STR_LEN], const char studio[MAX_STR_LEN], int year, float BO_total, int score, ReviewNode *head)
{
    /*
     * This function inserts a new movie review into the linked list.
     *
     * The function takes as input parameters the data neede to fill-in the review,
     * as well as apointer to the current head of the linked list.
     *
     * If head==NULL, then the list is still empty.
     *
     * The function inserts the new movie review *at the head* of the linked list,
     * and returns the pointer to the new head node.
     *
     * The function MUST check that the movie is not already in the list before
     * inserting (there should be no duplicate entries). If a movie with matching
     * title, studio, and year is already in the list, nothing is inserted and the
     * function returns the current list head.
     */

    /***************************************************************************/
    /**********  TO DO: Complete this function *********************************/
    /***************************************************************************/


    // If movie already exists, print message and return existing head
    ReviewNode *p = findMovieReview(title, studio, year, head);
    if (p != NULL) {
      p->review.scores_head = insertNewScore(p->review.scores_head, score);
    }
    else {
      // Creating a new ReviewNode and initializing it to given parameters
      ReviewNode *new_review = newMovieReviewNode();

      // Initializing the values to the parameters
      strcpy(new_review->review.movie_title, title);
      strcpy(new_review->review.movie_studio, studio);
      new_review->review.year = year;
      new_review->review.BO_total = BO_total;
      new_review->review.scores_head = newScoreNode();
      new_review->review.scores_head->score = score;
      new_review->next = NULL;

      // Inserting the movie at the head
      new_review->next = head;
      return new_review;
    }

    return head;	// <--- This should change when after you implement your solution
}

void printReviewScores(char title[MAX_STR_LEN], char studio[MAX_STR_LEN], int year, ReviewNode *head) {
  ReviewNode *p = findMovieReview(title, studio, year, head);

  if (p != NULL) {
    ScoreNode *current = p->review.scores_head;

    while (current != NULL) {
      printf("%d\n", current->score);
      current = current->next;
    }
  }
}

float getAverageScore(const char title[MAX_STR_LEN], const char studio[MAX_STR_LEN], int year, ReviewNode *head) {
  ReviewNode *p = findMovieReview(title, studio, year, head);

  if (p == NULL) {
    return -1;
  }

  int count = 0;
  float total = 0.0;
  ScoreNode *current = p->review.scores_head;

  while (current != NULL) {
    count++;
    total = total + current->score;
    current = current->next;
  }

  float average = total / count;
  return average;
}

int countReviews(ReviewNode *head)
{
  /*
   * This function returns the length of the current linked list. This requires
   * list traversal.
   */

    /***************************************************************************/
    /**********  TO DO: Complete this function *********************************/
    /***************************************************************************/

    int count = 0;
    ReviewNode *p = head;


    while (p != NULL) {
      count++;
      p = p->next;
    }

    return count;	// <--- This should change when after you implement your solution
}


ReviewNode *findPrevReview(ReviewNode *head, ReviewNode *target) {

  ReviewNode *q = head;

  while (q->next != NULL) {
    if (q->next == target) {
      return q;
    }
    q = q->next;
  }
  return NULL;
}

ScoreNode *deleteScores(ReviewNode *rev) {
  ScoreNode *p = rev->review.scores_head;

  while (p != NULL) {
    ScoreNode *q = p->next;
    free(p);
    p = q;
  }
  return p;
}

ReviewNode *deleteMovieReview(const char title[MAX_STR_LEN], const char studio[MAX_STR_LEN], int year, ReviewNode *head)
{
    /*
     * This function removes a review matching the input query from the linked list. If no such review can
     * be found, it does nothing.
     *
     * The function returns a pointer to the head of the linked list (which may have changed as a result
     * of the deletion process)
     */

    /***************************************************************************/
    /**********  TO DO: Complete this function *********************************/
    /***************************************************************************/
    ReviewNode *p = findMovieReview(title, studio, year, head);

    // If we found the review
    if (p != NULL) {
      // If the review is at the head, free the head and return pointer to second node
      if (p == head) {
        head = p->next;
        free(p);
      }
      else {
        // Found the node we want to delete, and it is not at the head
        // Sets the pointer to the next node of the predecessor to the link of p
        ReviewNode *q = findPrevReview(head, p);
        if (q != NULL) {
          q->next = p->next;
          deleteScores(p);
          free(p);
        }

      }
    }

    return head;	// <--- This should change when after you implement your solution
}

void printReview(ReviewNode *review) {
  printf("%s\n", review->review.movie_title);
  printf("\n%s\n", review->review.movie_studio);
  printf("\n%d\n", review->review.year);
  printf("%f\n", review->review.BO_total);
  printf("**********************\n");
}

void printMovieReviews(ReviewNode *head)
{
    /*
     * This function prints out all the reviews in the linked list, one after another.
     * Each field in the review is printed in a separate line, with *no additional text*
     * (that means, the only thing printed is the value of the corresponding field).
     *
     * Reviews are separated from each other by a line of
     * "*******************"
     *
     * See the Assignment handout for a sample of the output that should be produced
     * by this function
     */

    /***************************************************************************/
    /**********  TO DO: Complete this function *********************************/
    /***************************************************************************/

    ReviewNode *p = head;


    while (p != NULL) {
      printReview(p);
      p = p->next;
    }
}

void queryReviewsByStudio(const char studio[MAX_STR_LEN], ReviewNode *head)
{
    /*
     * This function looks for reviews whose studio matches the input query.
     * It prints out the contents of all reviews matching the query in exactly
     * the same format used by the printMovieReviews() function above.
     */

    /***************************************************************************/
    /**********  TO DO: Complete this function *********************************/
    /***************************************************************************/

    ReviewNode *p = head;

    while (p != NULL) {
      if (strcmp(p->review.movie_studio, studio) == 0) {
        printReview(p);
      }
      p = p->next;
    }
}

void queryReviewsByScore(int min_score, ReviewNode *head)
{
    /*
     * This function looks for reviews whose score is greater than, or equal to
     * the input 'min_score'.
     * It prints out the contents of all reviews matching the query in exactly
     * the same format used by the printMovieReviews() function above.
     */

    /***************************************************************************/
    /**********  TO DO: Complete this function *********************************/
    /***************************************************************************/

    ReviewNode *p = NULL;
    p = head;

    while (p != NULL) {
      float avgscore = getAverageScore(p->review.movie_title, p->review.movie_studio, p->review.year, head);
      if (avgscore >= min_score) {
        printReview(p);
      }
      p = p->next;
    }
}

ReviewNode *deleteReviewList(ReviewNode *head)
{
  /*
   * This function deletes the linked list of movie reviews, releasing all the
   * memory allocated to the nodes in the linked list.
   *
   * Returns a NULL pointer so that the head of the list can be set to NULL
   * after deletion.
   */

    /***************************************************************************/
    /**********  TO DO: Complete this function *********************************/
    /***************************************************************************/
    ReviewNode *p = head;


    while (p != NULL) {
      ReviewNode *q = p->next;
      deleteScores(p);
      free(p);
      p = q;
    }
    return p;	// <--- This should change when after you implement your solution
}


ReviewNode *sortReviewsByTitle(ReviewNode *head)
{
  /*
   * This function sorts the list of movie reviews in ascending order of movie
   * title. If duplicate movie titles exist, the order is arbitrary (i.e. you
   * can choose which one goes first).
   *
   * However you implement this function, it must return a pointer to the head
   * node of the sorted list.
   */

    /***************************************************************************/
    /**********  TO DO: Complete this function *********************************/
    /***************************************************************************/

    // If there is 0 or 1 reviews in the list, return head
    if (head == NULL || head->next == NULL) {
      return head;
    }

    int swap = 1;
    while (swap == 1) {
      swap = 0;
      ReviewNode *p = NULL;
      p = head;
      while (p->next != NULL) {
        if (strcmp(p->review.movie_title, p->next->review.movie_title) > 0) {
          Movie_Review temp = p->review;
          p->review = p->next->review;
          p->next->review = temp;
          swap = 1;
        }
        p = p->next;
      }
    }

    return head;	// <--- This should change when after you implement your solution
}
