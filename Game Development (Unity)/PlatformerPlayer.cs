using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class PlatformerPlayer : MonoBehaviour
{
    private Rigidbody2D rb;
    private BoxCollider2D box;
    private Animator anim;

    [Header("Walk")]
    public float speed;
    public float currentSpeed;
    public float speedMultiplier;
    public float speedLimit;
    private float moveDir;

    [Header("Jump")]
    public Transform feetpos;
    public LayerMask whatIsground;
    public float checkRadius;
    public bool isGrounded;
    public float jump;
    private float currentJump;
    public float jumpTime;
    private float jumpTimeCounter;
    private bool isJumping;

    [Header("Fall")]
    public float fallMultiplier;
    public float fallSpeedLimit;
    public float sitFall;

    [Header("WallSlide")]
    public Transform wallTouch;
    public float slideSpeed;
    private bool wallCheck;
    private bool wallSlide;

    [Header("WallJump")]
    public float xWallJump;
    public float yWallJump;
    private float addForce;

    [Header("Sit")]
    public float roll;
    public float sitHeight;
    public float standHeight;
    public float offSet;
    
    //anim
    private bool isWalking;
    private bool isFacingRight = true;
    private bool isSitting;

    void Start()
    {
        rb = GetComponent<Rigidbody2D>();
        anim = GetComponent<Animator>();
        box = GetComponent<BoxCollider2D>();

        currentSpeed = speed;
        currentJump = jump;
    }

    void FixedUpdate() 
    {
        rb.velocity = new Vector2(moveDir * currentSpeed + addForce , rb.velocity.y);
    }

    public void Update() 
    {
        //currentVelocity
        anim.SetFloat("xVelocity",rb.velocity.x);
        anim.SetFloat("yVelocity",rb.velocity.y);

        //animation
        anim.SetBool("isWalking",isWalking);
        anim.SetBool("isGrounded",isGrounded);

        //walk
        moveDir = Input.GetAxisRaw("Horizontal");

        if(currentSpeed < speedLimit && isGrounded == true){
            currentSpeed += speedMultiplier * Time.deltaTime;
        }
        if(rb.velocity.x == 0){
            currentSpeed = speed;
        }

        if(isGrounded = true && moveDir != 0){
            isWalking = true;
        }else{
            isWalking = false;
        }

        //jump
        isGrounded = Physics2D.OverlapCircle(feetpos.position ,checkRadius ,whatIsground);

        if(isGrounded == true && Input.GetButtonDown("Jump")){
            isJumping = true;
            jumpTimeCounter = jumpTime;
            rb.velocity = Vector2.up * currentJump;
        }

        if(Input.GetButton("Jump") && isJumping && !wallCheck){
            if(jumpTimeCounter > 0){
                rb.velocity = Vector2.up * currentJump;
                jumpTimeCounter -= Time.deltaTime;
            }else{
                isJumping = false;
            }
        }
        if(Input.GetButtonUp("Jump")){
            isJumping = false;
            wallSlide = false;
        }

        //fall
        if(rb.velocity.y < 0 && rb.velocity.y < fallSpeedLimit){
            rb.velocity += Vector2.up * Physics2D.gravity.y * (fallMultiplier -1) * Time.deltaTime;
        }else if(rb.velocity.y > 0 && !Input.GetButton("Jump")){
            rb.velocity += Vector2.up * Physics2D.gravity.y * (fallMultiplier/2) * Time.deltaTime;
        }

        //wallSlide
        wallCheck = Physics2D.Raycast(wallTouch.position,wallTouch.TransformDirection(Vector2.right), checkRadius ,whatIsground);

        if(wallCheck && !isGrounded && Input.GetButton("Jump")){
            rb.velocity = Vector2.up * Mathf.Clamp(rb.velocity.y, -slideSpeed, float.MaxValue);
            wallSlide = true;
            isJumping = false;
        }if(wallCheck){
            currentSpeed = 1;
        }

        if(isGrounded){
            addForce = 0;
            wallSlide = false;
        }if(addForce != 0){
            addForce -= addForce * Time.deltaTime;
        }

        //flip
        if(isFacingRight && moveDir < 0){
            Flip();
            //wallJump
            if(wallSlide){
                rb.velocity = Vector2.up * yWallJump;
                addForce = -xWallJump;

                wallSlide = false;
            }
        }else if(!isFacingRight && moveDir > 0){
            Flip();
            //wallJump
            if(wallSlide){
                rb.velocity = Vector2.up * yWallJump;
                addForce = xWallJump;

                wallSlide = false;
            }
        }

        //sit
        if(Input.GetButtonDown("Fire3")){
            rb.velocity = Vector2.up * -sitFall;
        }
        if(Input.GetButton("Fire3"))
        {
            anim.SetBool("isSitting", true);
            currentSpeed = 0;
            currentJump = 0;
            //You can do the box and vector at anim
            box.size = new Vector2(box.size.x ,sitHeight);
            box.offset = new Vector2(-0.05f ,offSet);
        }
        if(Input.GetButtonUp("Fire3")){
            anim.SetBool("isSitting",false);
            currentSpeed = speed;
            currentJump = jump;
            box.size = new Vector2(box.size.x ,standHeight);
            box.offset = new Vector2(-0.05f ,-0.05f);
        }

        //roll
        if(Input.GetButton("Fire3") && Input.GetButtonDown("Jump"))
        {
            anim.SetTrigger("roll");
            if(isFacingRight){
                addForce = roll;
            }else if(!isFacingRight){
                addForce = -roll;
            }
        }
    }

    void Flip()
    {
        currentSpeed = speed;
        isFacingRight = !isFacingRight;
        transform.Rotate(0, 180, 0);
    }

    void OnDrawGizmos()
    {
        Gizmos.DrawWireSphere(feetpos.position,checkRadius);
    }
}